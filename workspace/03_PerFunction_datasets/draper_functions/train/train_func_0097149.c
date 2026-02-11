DumpSegment64Command(MachOObject &Obj,
                               const MachOObject::LoadCommandInfo &LCI) {
  InMemoryStruct<macho::Segment64LoadCommand> SLC;
  Obj.ReadSegment64LoadCommand(LCI, SLC);
  if (!SLC)
    return Error("unable to read segment load command");

  DumpSegmentCommandData(StringRef(SLC->Name, 16), SLC->VMAddress,
                         SLC->VMSize, SLC->FileOffset, SLC->FileSize,
                         SLC->MaxVMProtection, SLC->InitialVMProtection,
                         SLC->NumSections, SLC->Flags);


  int Res = 0;
  outs() << "  ('sections', [\n";
  for (unsigned i = 0; i != SLC->NumSections; ++i) {
    InMemoryStruct<macho::Section64> Sect;
    Obj.ReadSection64(LCI, i, Sect);
    if (!SLC) {
      Res = Error("unable to read section '" + Twine(i) + "'");
      break;
    }

    if ((Res = DumpSectionData(Obj, i, StringRef(Sect->Name, 16),
                               StringRef(Sect->SegmentName, 16), Sect->Address,
                               Sect->Size, Sect->Offset, Sect->Align,
                               Sect->RelocationTableOffset,
                               Sect->NumRelocationTableEntries, Sect->Flags,
                               Sect->Reserved1, Sect->Reserved2,
                               Sect->Reserved3)))
      break;
  }
  outs() << "  ])\n";

  return 0;
}
