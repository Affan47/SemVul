es_assign_num(struct variable *v, double val)
{
  do_output(LOG_CAT_INFO, LOG_AREA_MAIN, " %s := %g\n", v->name, val);
  switch(v->type) {
  case VAR_FLOAT:  v->v.num  =      val; break;
  case VAR_INT:    v->v.vint = (int)val; break;
  default:
    do_output(LOG_CAT_ERROR, LOG_AREA_MAIN,
	      "Assignment of numerical value to nonnumerical "
	      "variable %s ignored.\n", v->name);
  }
}
