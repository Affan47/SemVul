collectBasicVars()
{
  TRACE_MSG("model", "collectBasicVars() {");

  d_varModelMap.clear();
  d_varAssignments.clear();
  d_basicModelVars.clear();
  d_simplifiedModelVars.clear();

  vector<Expr> stack(d_vars.begin(), d_vars.end());
  size_t lastSize(0);
  while(stack.size() > 0) {
    Expr var(stack.back());
    stack.pop_back();
    if(d_varModelMap.count(var) > 0) continue;
    Theorem findThm(find(var));
    if(findThm.getRHS()!=var) {
      d_simplifiedModelVars[var] = findThm;
      stack.push_back(findThm.getRHS());
      TRACE("model", "collectBasicVars: simplified var: ", findThm.getExpr(), "");
      continue;
    }
    lastSize = stack.size();
    TRACE("model", "getModelTerm(", var, ") {");
    getModelTerm(var, stack);
    TRACE("model", "getModelTerm => ",
	  Expr(RAW_LIST, stack, getEM()), " }");
    if(stack.size() == lastSize) {

      TRACE("model", "collectBasicVars: adding primitive var: ", var, "");
      d_basicModelVars.push_back(var);
      if(var.isTerm()) {
	Theory* t1 = theoryOf(var);
	Theory* t2 = theoryOf(getBaseType(var).getExpr().getKind());
	if(t1 != t2) {
	  TRACE("model", "collectBasicVars: adding shared var: ", var, "");
	  t1->addSharedTerm(var);
	  t2->addSharedTerm(var);
	}
      }
    } else {
      vector<Expr>& kids = d_varModelMap[var];
      for(size_t i=lastSize; i<stack.size(); ++i) {
	DebugAssert(stack[i] != var, "Primitive var was pushed on "
		    "the stack in computeModelTerm(): "+var.toString());
	kids.push_back(stack[i]);
      }
      TRACE("model", "collectBasicVars: var="+var.toString()
	    +" maps into vars=", Expr(RAW_LIST, kids, getEM()), "");
    }
  }
  TRACE_MSG("model", "collectBasicVars() => }");
}
