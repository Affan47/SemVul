expandNeq(const Theorem& neqThrm)
{
  Expr e = neqThrm.getExpr();
  if(CHECK_PROOFS)
    CHECK_SOUND(e.getKind() == NOT, "expected not expression" + e.toString());
  e=e[0];
  Expr e0 = e[0].getType().getExpr() , e1 = e[1].getType().getExpr();
  if(CHECK_PROOFS)
    {
    CHECK_SOUND(e.getKind() == EQ,
		"equation expression expected \n" + e.toString());
    CHECK_SOUND(e0.arity()==e1.arity() && e0.getOpKind() == e1.getOpKind(),
		"equation types mismatch \n" + e.toString());
    CHECK_SOUND(e0.getOpKind() == RECORD_TYPE || e0.getOpKind() == TUPLE_TYPE,
		"expected TUPLES or RECORDS \n" + e.toString());
    }
  std::vector<Expr> orChildren;
  for(int i=0; i<e0.arity();i++)
  {
    Expr lhs, rhs;
    switch(e0.getOpKind()) {
    case RECORD_TYPE: {
      const string& field(getField(e0, i));
      DebugAssert(field == getField(e1, i),
		  "equation types mismatch \n" + neqThrm.getExpr().toString());
      lhs = recordSelect(e[0], field);
      rhs = recordSelect(e[1], field);
      break;
    }
    case TUPLE_TYPE: {
      lhs = tupleSelect(e[0], i);
      rhs = tupleSelect(e[1], i);
      break;
      }
    default:
      DebugAssert(false, "RecordsTheoremProducer::expandNeq: "
		  "Type must be TUPLE or RECORD: "+e0.toString());
    }
    Expr eq = lhs.getType().isBool()? lhs.iffExpr(rhs) : lhs.eqExpr(rhs);
    orChildren.push_back(!eq);
  }
  Proof pf;
  if(withProof())
    pf= newPf("rewrite_record_literal_update", e, neqThrm.getProof());
  return newTheorem(orExpr(orChildren), neqThrm.getAssumptionsRef(), pf);
}
