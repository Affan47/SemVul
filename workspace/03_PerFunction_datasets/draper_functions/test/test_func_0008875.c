varExpr(const string& name, const Type& type)
{

  if(d_dump) {
    d_translator->dump(Expr(CONST, idExpr(name), type.getExpr()));
  }
  return d_theoryCore->newVar(name, type);
}
