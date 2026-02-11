getSymbolByIndex(unsigned Index) const {
  DataRefImpl DRI;
  if (!SymtabLoadCmd)
    return basic_symbol_iterator(SymbolRef(DRI, this));

  MachO::symtab_command Symtab = getSymtabLoadCommand();
  if (Index >= Symtab.nsyms)
    report_fatal_error("Requested symbol index is out of range.");
  unsigned SymbolTableEntrySize =
    is64Bit() ? sizeof(MachO::nlist_64) : sizeof(MachO::nlist);
  DRI.p = reinterpret_cast<uintptr_t>(getPtr(this, Symtab.symoff));
  DRI.p += Index * SymbolTableEntrySize;
  return basic_symbol_iterator(SymbolRef(DRI, this));
}
