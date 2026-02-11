isInvariantLoad(AliasAnalysis *AA) const {

  if (!MCID->mayLoad())
    return false;


  if (memoperands_empty())
    return false;

  const MachineFrameInfo *MFI = getParent()->getParent()->getFrameInfo();

  for (mmo_iterator I = memoperands_begin(),
       E = memoperands_end(); I != E; ++I) {
    if ((*I)->isVolatile()) return false;
    if ((*I)->isStore()) return false;

    if (const Value *V = (*I)->getValue()) {

      if (const PseudoSourceValue *PSV = dyn_cast<PseudoSourceValue>(V))
        if (PSV->isConstant(MFI))
          continue;

      if (AA && AA->pointsToConstantMemory(
                      AliasAnalysis::Location(V, (*I)->getSize(),
                                              (*I)->getTBAAInfo())))
        continue;
    }


    return false;
  }


  return true;
}
