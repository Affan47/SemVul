set_break(cmd_options *co,
				  Expression *pExpr1,
				  Expression *pExpr2,
				  bool bLog)

{

  if (!co) {
    list();
    return MAX_BREAKPOINTS;
  }

  unsigned int bit_flag = co->value;
  if (!pExpr1)
    return set_break(bit_flag,bLog);


  int i = pExpr1 ? pExpr1->set_break(MapBreakActions(co->value),
				     (bLog ? gpsimObject::eActionLog : gpsimObject::eActionHalt), pExpr2) : -1;
  if (i>=0) {
    get_bp().dump1(i);
    return i;
  }

  unsigned int b = MAX_BREAKPOINTS;
  delete pExpr1;
  delete pExpr2;

  return b;

}
