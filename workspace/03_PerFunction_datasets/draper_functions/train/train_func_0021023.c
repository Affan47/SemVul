GetSizeOfEncodedValue(unsigned Encoding) const {
  if (Encoding == dwarf::DW_EH_PE_omit)
    return 0;

  switch (Encoding & 0x07) {
  default: assert(0 && "Invalid encoded value.");
  case dwarf::DW_EH_PE_absptr: return TM.getTargetData()->getPointerSize();
  case dwarf::DW_EH_PE_udata2: return 2;
  case dwarf::DW_EH_PE_udata4: return 4;
  case dwarf::DW_EH_PE_udata8: return 8;
  }
}
