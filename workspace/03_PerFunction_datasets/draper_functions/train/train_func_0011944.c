addSymbol(const SymbolRef &Symbol,
                                                  uint64_t SymbolSize,
                                                  DataExtractor *OpdExtractor,
                                                  uint64_t OpdAddress) {
  SymbolRef::Type SymbolType = Symbol.getType();
  if (SymbolType != SymbolRef::ST_Function && SymbolType != SymbolRef::ST_Data)
    return std::error_code();
  ErrorOr<uint64_t> SymbolAddressOrErr = Symbol.getAddress();
  if (auto EC = SymbolAddressOrErr.getError())
    return EC;
  uint64_t SymbolAddress = *SymbolAddressOrErr;
  if (OpdExtractor) {


    uint64_t OpdOffset = SymbolAddress - OpdAddress;
    uint32_t OpdOffset32 = OpdOffset;
    if (OpdOffset == OpdOffset32 &&
        OpdExtractor->isValidOffsetForAddress(OpdOffset32))
      SymbolAddress = OpdExtractor->getAddress(&OpdOffset32);
  }
  ErrorOr<StringRef> SymbolNameOrErr = Symbol.getName();
  if (auto EC = SymbolNameOrErr.getError())
    return EC;
  StringRef SymbolName = *SymbolNameOrErr;

  if (Module->isMachO() && SymbolName.size() > 0 && SymbolName[0] == '_')
    SymbolName = SymbolName.drop_front();


  auto &M = SymbolType == SymbolRef::ST_Function ? Functions : Objects;
  SymbolDesc SD = { SymbolAddress, SymbolSize };
  M.insert(std::make_pair(SD, SymbolName));
  return std::error_code();
}
