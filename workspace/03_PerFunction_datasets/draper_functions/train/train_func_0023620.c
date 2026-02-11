dump(const PDBSymbolTypeFunctionArg &Symbol) {


  uint32_t TypeId = Symbol.getTypeId();
  auto Type = Symbol.getSession().getSymbolById(TypeId);
  if (!Type)
    return;
  Type->dump(*this);
}
