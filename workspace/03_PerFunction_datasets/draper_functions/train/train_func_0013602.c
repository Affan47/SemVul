isOffsetFoldingLegal(const GlobalAddressSDNode *GA) const {

  if (getTargetMachine().getRelocationModel() == Reloc::Static)
    return true;


  if (getTargetMachine().getRelocationModel() == Reloc::DynamicNoPIC &&
      GA &&
      !GA->getGlobal()->isDeclaration() &&
      !GA->getGlobal()->isWeakForLinker())
    return true;


  return false;
}
