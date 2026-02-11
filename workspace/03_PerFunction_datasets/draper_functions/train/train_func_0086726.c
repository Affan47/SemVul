expandRecord(const Expr& e) {
  Type tp(d_theoryRecords->getBaseType(e));
  if(CHECK_PROOFS) {
    CHECK_SOUND(isRecordType(tp),
		"expandRecord("+e.toString()+"): not a record type");
  }
  const vector<Expr>& fields = getFields(tp.getExpr());
  vector<Expr> kids;
  for(vector<Expr>::const_iterator i=fields.begin(), iend=fields.end();
      i!=iend; ++i)
    kids.push_back(recordSelect(e, (*i).getString()));
  Proof pf;
  if(withProof()) pf = newPf("expand_record", e);
  return newRWTheorem(e, recordExpr(fields, kids), Assumptions::emptyAssump(), pf);
}
