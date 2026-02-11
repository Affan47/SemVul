setValue(int val, const Clause& c, int idx) {
  if(d_val==NULL) {

    d_val = new(true) CDO<int>(d_vm->getCM()->getCurrentContext(), 0, 0);
    IF_DEBUG(d_val->setName("CDO[VariableValue::d_val]");)
  }
  if(d_scope==NULL) {
    d_scope = new(true) CDO<int>(d_vm->getCM()->getCurrentContext());
    IF_DEBUG(d_scope->setName("CDO[VariableValue::d_scope]");)
  }
  if(d_ante==NULL) {
    d_ante = new(true) CDO<Clause>(d_vm->getCM()->getCurrentContext());
    IF_DEBUG(d_ante->setName("CDO[VariableValue::d_ante]");)
  }
  if(d_anteIdx==NULL) {
    d_anteIdx = new(true) CDO<int>(d_vm->getCM()->getCurrentContext());
    IF_DEBUG(d_anteIdx->setName("CDO[VariableValue::d_anteIdx]");)
  }


  int scope(c.getScope());
  for(int i=0, iend=c.size(); i!=iend; ++i) {
    if(i!=idx) {
      int s(c[i].getScope());
      if(s > scope) scope = s;
      DebugAssert(c[i].getValue() != 0,
		  "VariableValue::setValue(ante): literal has no value: "
		  "i="+int2string(i)+" in\n clause = "
		  +c.toString());
    }
  }

  d_val->set(val, scope);
  d_scope->set(scope, scope);
  d_ante->set(c, scope);
  d_anteIdx->set(idx, scope);

  if(!getTheorem().isNull()) d_thm->set(Theorem(), scope);

  IF_DEBUG(Expr l((idx == -1)? getExpr().getEM()->falseExpr()
		  : c[idx].getExpr());)
  DebugAssert((val > 0 && l == getExpr())
	      || (val < 0 && l.isNot() && l[0] == getExpr()),
	      "VariableValue::setValue(val = " + int2string(val)
	      + ", c = " + c.toString() + ", idx = " + int2string(idx)
	      + "):\n expr = " + getExpr().toString()
	      + "\n literal = " + l.toString());
}
