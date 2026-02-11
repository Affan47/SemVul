newPf(const string& name,
			     const Expr& e,
			     const vector<Expr>& args) {
  vector<Expr> kids;
  kids.push_back(d_em->newVarExpr(name));
  kids.push_back(e);
  kids.insert(kids.end(), args.begin(), args.end());
  return Proof(Expr(d_pfOp, kids));
}
