getSymbolFlags(DataRefImpl DRI) const {
  MachO::nlist_base Entry = getSymbolTableEntryBase(this, DRI);

  uint8_t MachOType = Entry.n_type;
  uint16_t MachOFlags = Entry.n_desc;

  uint32_t Result = SymbolRef::SF_None;

  if ((MachOType & MachO::N_TYPE) == MachO::N_INDR)
    Result |= SymbolRef::SF_Indirect;

  if (MachOType & MachO::N_STAB)
    Result |= SymbolRef::SF_FormatSpecific;

  if (MachOType & MachO::N_EXT) {
    Result |= SymbolRef::SF_Global;
    if ((MachOType & MachO::N_TYPE) == MachO::N_UNDF) {
      if (getNValue(DRI))
        Result |= SymbolRef::SF_Common;
      else
        Result |= SymbolRef::SF_Undefined;
    }

    if (!(MachOType & MachO::N_PEXT))
      Result |= SymbolRef::SF_Exported;
  }

  if (MachOFlags & (MachO::N_WEAK_REF | MachO::N_WEAK_DEF))
    Result |= SymbolRef::SF_Weak;

  if (MachOFlags & (MachO::N_ARM_THUMB_DEF))
    Result |= SymbolRef::SF_Thumb;

  if ((MachOType & MachO::N_TYPE) == MachO::N_ABS)
    Result |= SymbolRef::SF_Absolute;

  return Result;
}
