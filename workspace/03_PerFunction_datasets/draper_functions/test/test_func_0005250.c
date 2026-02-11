addAsmGlobalSymbolUndef(const char *name) {
  StringMap<NameAndAttributes>::value_type &entry =
    _undefines.GetOrCreateValue(name);

  _asm_undefines.push_back(entry.getKey().data());


  if (entry.getValue().name)
    return;

  uint32_t attr = LTO_SYMBOL_DEFINITION_UNDEFINED;;
  attr |= LTO_SYMBOL_SCOPE_DEFAULT;
  NameAndAttributes info;
  info.name = entry.getKey().data();
  info.attributes = (lto_symbol_attributes)attr;

  entry.setValue(info);
}
