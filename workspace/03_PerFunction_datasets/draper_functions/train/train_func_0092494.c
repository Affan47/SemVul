acs_rlink_is_enabled(Rlink *rlink, Kwv *kwv, Kwv *kwv_args, Credentials *cr)
{
  char *result_str;
  Acs_expr_result st;

  if ((st = acs_eval(rlink->expr, kwv, kwv_args, cr, &result_str))
	  == ACS_EXPR_TRUE) {
	log_msg((LOG_TRACE_LEVEL, "rlink evaluates to: \"%s\"", result_str));
	return(result_str);
  }

  log_msg((LOG_TRACE_LEVEL, "rlink disabled (%s)",
		   (st == ACS_EXPR_FALSE) ? "False" : "Error"));
  return(NULL);
}
