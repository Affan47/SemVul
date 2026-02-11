findPPC64TOCSection(const ELFObjectFileBase &Obj,
                                         ObjSectionToIDMap &LocalSections,
                                         RelocationValueRef &Rel) {


  Rel.SymbolName = nullptr;
  Rel.SectionID = 0;


  for (auto &Section: Obj.sections()) {
    StringRef SectionName;
    check(Section.getName(SectionName));

    if (SectionName == ".got"
        || SectionName == ".toc"
        || SectionName == ".tocbss"
        || SectionName == ".plt") {
      Rel.SectionID = findOrEmitSection(Obj, Section, false, LocalSections);
      break;
    }
  }


  Rel.Addend = 0x8000;
}
