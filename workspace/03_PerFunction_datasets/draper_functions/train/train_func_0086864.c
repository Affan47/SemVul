constructVariableDIE(DbgVariable &DV,
                                            const LexicalScope &Scope,
                                            DIE *&ObjectPointer) {
  auto Var = constructVariableDIE(DV, Scope.isAbstractScope());
  if (DV.isObjectPointer())
    ObjectPointer = Var;
  return Var;
}
