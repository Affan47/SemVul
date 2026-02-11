GVIsIndirectSymbol(const GlobalValue *GV,
                                 Reloc::Model RelocM) const {
  if (RelocM == Reloc::Static)
    return false;

  bool isDef = GV->isStrongDefinitionForLinker();

  if (!isTargetMachO()) {

    if (GV->hasLocalLinkage() || GV->hasHiddenVisibility())
      return false;
    return true;
  } else {


    if (isDef)
      return false;


    if (!GV->hasHiddenVisibility())
      return true;

    if (RelocM == Reloc::PIC_) {


      if (GV->isDeclarationForLinker() || GV->hasCommonLinkage())

        return true;
    }
  }

  return false;
}
