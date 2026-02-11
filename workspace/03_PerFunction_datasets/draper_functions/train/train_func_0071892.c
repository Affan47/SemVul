SectionForGlobal(const GlobalValue *GV, SectionKind Kind, Mangler *Mang,
                 const TargetMachine &TM) const {

  if (GV->hasSection())
    return getExplicitSectionGlobal(GV, Kind, Mang, TM);


  return SelectSectionForGlobal(GV, Kind, Mang, TM);
}
