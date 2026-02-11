DumpDysymtabCommand(MachOObject &Obj,
                             const MachOObject::LoadCommandInfo &LCI) {
  InMemoryStruct<macho::DysymtabLoadCommand> DLC;
  Obj.ReadDysymtabLoadCommand(LCI, DLC);
  if (!DLC)
    return Error("unable to read segment load command");

  outs() << "  ('ilocalsym', " << DLC->LocalSymbolsIndex << ")\n";
  outs() << "  ('nlocalsym', " << DLC->NumLocalSymbols << ")\n";
  outs() << "  ('iextdefsym', " << DLC->ExternalSymbolsIndex << ")\n";
  outs() << "  ('nextdefsym', " << DLC->NumExternalSymbols << ")\n";
  outs() << "  ('iundefsym', " << DLC->UndefinedSymbolsIndex << ")\n";
  outs() << "  ('nundefsym', " << DLC->NumUndefinedSymbols << ")\n";
  outs() << "  ('tocoff', " << DLC->TOCOffset << ")\n";
  outs() << "  ('ntoc', " << DLC->NumTOCEntries << ")\n";
  outs() << "  ('modtaboff', " << DLC->ModuleTableOffset << ")\n";
  outs() << "  ('nmodtab', " << DLC->NumModuleTableEntries << ")\n";
  outs() << "  ('extrefsymoff', " << DLC->ReferenceSymbolTableOffset << ")\n";
  outs() << "  ('nextrefsyms', "
         << DLC->NumReferencedSymbolTableEntries << ")\n";
  outs() << "  ('indirectsymoff', " << DLC->IndirectSymbolTableOffset << ")\n";
  outs() << "  ('nindirectsyms', "
         << DLC->NumIndirectSymbolTableEntries << ")\n";
  outs() << "  ('extreloff', " << DLC->ExternalRelocationTableOffset << ")\n";
  outs() << "  ('nextrel', " << DLC->NumExternalRelocationTableEntries << ")\n";
  outs() << "  ('locreloff', " << DLC->LocalRelocationTableOffset << ")\n";
  outs() << "  ('nlocrel', " << DLC->NumLocalRelocationTableEntries << ")\n";


  int Res = 0;
  outs() << "  ('_indirect_symbols', [\n";
  for (unsigned i = 0; i != DLC->NumIndirectSymbolTableEntries; ++i) {
    InMemoryStruct<macho::IndirectSymbolTableEntry> ISTE;
    Obj.ReadIndirectSymbolTableEntry(*DLC, i, ISTE);
    if (!ISTE) {
      Res = Error("unable to read segment load command");
      break;
    }

    outs() << "    # Indirect Symbol " << i << "\n";
    outs() << "    (('symbol_index', "
           << format("0x%x", ISTE->Index) << "),),\n";
  }
  outs() << "  ])\n";

  return Res;
}
