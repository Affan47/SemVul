processByValArgument(CallSite CS, unsigned ArgNo) {
  if (TD == 0) return false;


  Value *ByValArg = CS.getArgument(ArgNo);
  Type *ByValTy = cast<PointerType>(ByValArg->getType())->getElementType();
  uint64_t ByValSize = TD->getTypeAllocSize(ByValTy);
  MemDepResult DepInfo =
    MD->getPointerDependencyFrom(AliasAnalysis::Location(ByValArg, ByValSize),
                                 true, CS.getInstruction(),
                                 CS.getInstruction()->getParent());
  if (!DepInfo.isClobber())
    return false;


  MemCpyInst *MDep = dyn_cast<MemCpyInst>(DepInfo.getInst());
  if (MDep == 0 || MDep->isVolatile() ||
      ByValArg->stripPointerCasts() != MDep->getDest())
    return false;


  ConstantInt *C1 = dyn_cast<ConstantInt>(MDep->getLength());
  if (C1 == 0 || C1->getValue().getZExtValue() < ByValSize)
    return false;


  unsigned ByValAlign = CS.getParamAlignment(ArgNo+1);
  if (ByValAlign == 0) return false;


  if (MDep->getAlignment() < ByValAlign &&
      getOrEnforceKnownAlignment(MDep->getSource(),ByValAlign, TD) < ByValAlign)
    return false;


  MemDepResult SourceDep =
    MD->getPointerDependencyFrom(AliasAnalysis::getLocationForSource(MDep),
                                 false, CS.getInstruction(), MDep->getParent());
  if (!SourceDep.isClobber() || SourceDep.getInst() != MDep)
    return false;

  Value *TmpCast = MDep->getSource();
  if (MDep->getSource()->getType() != ByValArg->getType())
    TmpCast = new BitCastInst(MDep->getSource(), ByValArg->getType(),
                              "tmpcast", CS.getInstruction());

  DEBUG(dbgs() << "MemCpyOpt: Forwarding memcpy to byval:\n"
               << "  " << *MDep << "\n"
               << "  " << *CS.getInstruction() << "\n");


  CS.setArgument(ArgNo, TmpCast);
  ++NumMemCpyInstr;
  return true;
}
