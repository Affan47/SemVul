recordExpr(const string& field0, const Expr& expr0,
		     const string& field1, const Expr& expr1)
{
  vector<string> fields;
  vector<Expr> kids;
  fields.push_back(field0);
  fields.push_back(field1);
  kids.push_back(expr0);
  kids.push_back(expr1);
  sort2(fields, kids);
  return d_theoryRecords->recordExpr(fields, kids);
}
