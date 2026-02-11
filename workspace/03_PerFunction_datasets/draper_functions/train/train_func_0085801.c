symbol_end_impl() const {
  DataRefImpl DRI;
  if (!SymtabLoadCmd)
    return basic_symbol_iterator(SymbolRef(DRI, this));

  MachO::symtab_command Symtab = getSymtabLoadCommand();
  unsigned SymbolTableEntrySize = is64Bit() ?
    sizeof(MachO::nlist_64) :
    sizeof(MachO::nlist);
  unsigned Offset = Symtab.symoff +
    Symtab.nsyms * SymbolTableEntrySize;
  DRI.p = reinterpret_cast<uintptr_t>(getPtr(this, Offset));
  return basic_symbol_iterator(SymbolRef(DRI, this));
}
