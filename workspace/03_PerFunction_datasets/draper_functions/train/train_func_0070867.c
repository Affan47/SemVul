WriteAuxiliarySymbols(
                                        const COFFSymbol::AuxiliarySymbols &S) {
  for(COFFSymbol::AuxiliarySymbols::const_iterator i = S.begin(), e = S.end();
      i != e; ++i) {
    switch(i->AuxType) {
    case ATFunctionDefinition:
      WriteLE32(i->Aux.FunctionDefinition.TagIndex);
      WriteLE32(i->Aux.FunctionDefinition.TotalSize);
      WriteLE32(i->Aux.FunctionDefinition.PointerToLinenumber);
      WriteLE32(i->Aux.FunctionDefinition.PointerToNextFunction);
      WriteZeros(sizeof(i->Aux.FunctionDefinition.unused));
      break;
    case ATbfAndefSymbol:
      WriteZeros(sizeof(i->Aux.bfAndefSymbol.unused1));
      WriteLE16(i->Aux.bfAndefSymbol.Linenumber);
      WriteZeros(sizeof(i->Aux.bfAndefSymbol.unused2));
      WriteLE32(i->Aux.bfAndefSymbol.PointerToNextFunction);
      WriteZeros(sizeof(i->Aux.bfAndefSymbol.unused3));
      break;
    case ATWeakExternal:
      WriteLE32(i->Aux.WeakExternal.TagIndex);
      WriteLE32(i->Aux.WeakExternal.Characteristics);
      WriteZeros(sizeof(i->Aux.WeakExternal.unused));
      break;
    case ATFile:
      WriteBytes(StringRef(reinterpret_cast<const char *>(i->Aux.File.FileName),
                 sizeof(i->Aux.File.FileName)));
      break;
    case ATSectionDefinition:
      WriteLE32(i->Aux.SectionDefinition.Length);
      WriteLE16(i->Aux.SectionDefinition.NumberOfRelocations);
      WriteLE16(i->Aux.SectionDefinition.NumberOfLinenumbers);
      WriteLE32(i->Aux.SectionDefinition.CheckSum);
      WriteLE16(i->Aux.SectionDefinition.Number);
      Write8(i->Aux.SectionDefinition.Selection);
      WriteZeros(sizeof(i->Aux.SectionDefinition.unused));
      break;
    }
  }
}
