shouldOmitSectionDirective(StringRef SectionName) const {

  return SectionName == ".text" || SectionName == ".data" ||
        (SectionName == ".bss" && !usesELFSectionDirectiveForBSS());
}
