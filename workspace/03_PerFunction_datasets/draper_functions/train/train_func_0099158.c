getOrCreateSubprogramDIE(const DISubprogram *SP, bool Minimal) {


  DIE *ContextDIE =
      Minimal ? &getUnitDie() : getOrCreateContextDIE(resolve(SP->getScope()));

  if (DIE *SPDie = getDIE(SP))
    return SPDie;

  if (auto *SPDecl = SP->getDeclaration()) {
    if (!Minimal) {

      ContextDIE = &getUnitDie();

      getOrCreateSubprogramDIE(SPDecl);
    }
  }


  DIE &SPDie = createAndAddDIE(dwarf::DW_TAG_subprogram, *ContextDIE, SP);


  if (SP->isDefinition())
    return &SPDie;

  applySubprogramAttributes(SP, SPDie);
  return &SPDie;
}
