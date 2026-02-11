newPf(const string& name,
			     const vector<Proof>& pfs) {
  vector<Expr> kids;
  kids.push_back(d_em->newVarExpr(name));
  for(vector<Proof>::const_iterator i=pfs.begin(), iend=pfs.end();
      i != iend; ++i)
    kids.push_back(i->getExpr());
  return Proof(Expr(d_pfOp, kids));
}
