getProofQuery()
{
  if (d_lastQuery.isNull()){
    throw EvalException
      ("Invalid Query,n");
  }
  return d_lastQuery.getExpr();


}
