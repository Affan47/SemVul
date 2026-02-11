PrintRelocations(const ObjectFile *o) {
  error_code ec;
  for (section_iterator si = o->begin_sections(), se = o->end_sections();
                                                  si != se; si.increment(ec)){
    if (error(ec)) return;
    if (si->begin_relocations() == si->end_relocations())
      continue;
    StringRef secname;
    if (error(si->getName(secname))) continue;
    outs() << "RELOCATION RECORDS FOR [" << secname << "]:\n";
    for (relocation_iterator ri = si->begin_relocations(),
                             re = si->end_relocations();
                             ri != re; ri.increment(ec)) {
      if (error(ec)) return;

      uint64_t address;
      SmallString<32> relocname;
      SmallString<32> valuestr;
      if (error(ri->getTypeName(relocname))) continue;
      if (error(ri->getAddress(address))) continue;
      if (error(ri->getValueString(valuestr))) continue;
      outs() << address << " " << relocname << " " << valuestr << "\n";
    }
    outs() << "\n";
  }
}
