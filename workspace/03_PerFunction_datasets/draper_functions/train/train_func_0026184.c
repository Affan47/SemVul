newPf(const string& name,
			     const Expr& e,
			     const vector<Proof>& pfs) {
  vector<Expr> kids;
  kids.push_back(d_em->newVarExpr(name));
  kids.push_back(e);
  for(vector<Proof>::const_iterator i=pfs.begin(), iend=pfs.end();
      i != iend; ++i)
    kids.push_back(i->getExpr());
  return Proof(Expr(d_pfOp, kids));
}
