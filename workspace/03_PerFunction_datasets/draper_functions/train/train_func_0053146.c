func_ack(Lex_state *e, int nargs, Arglist *arglist, Expr_result *result)
{
  unsigned int ui;
  char *mode, *s1;
  Arglist *x;
  Dsvec *needed_notices, *notices;
  extern Dsvec *get_needed_notices(Dsvec *, char *mode);

  x = arglist;
  if (x == NULL) {
	seterr_e(e, result, "Invalid argument to 'ack' function");
	return(-1);
  }

  notices = dsvec_init(NULL, sizeof(char *));
  mode = "EXACT_MATCH";

  for (x = arglist; x != NULL; x = x->next) {
	if (!str_or_lit(x->result->value.token)) {
	  seterr_e(e, result, "Invalid argument to 'ack' function");
	  return(-1);
	}

	s1 = x->result->value.val.strval;
	if (strcaseeq(s1, "EXACT_MATCH") || strcaseeq(s1, "ALL_MATCH")) {
	  mode = s1;
	  x = x->next;
	  break;
	}

	if (uri_parse(s1) == NULL) {
	  seterr_e(e, result, "Invalid URI argument to 'ack' function");
	  return(-1);
	}
	dsvec_add_ptr(notices, s1);
  }

  if (x != NULL) {
	seterr_e(e, result, "Invalid argument to 'ack' function");
	return(-1);
  }


  for (ui = 0; ui < dsvec_len(notices); ui++) {
	log_msg((LOG_TRACE_LEVEL, "Rule wants ack for notice: %s",
			 (char *) dsvec_ptr_index(notices, ui)));
  }

  if ((needed_notices = get_needed_notices(notices, mode)) != NULL) {
	log_msg((LOG_TRACE_LEVEL, "Notices not yet acknowledged: %s",
			 strjoin(needed_notices, " ")));
	e->env->notices = needed_notices;
	longjmp(e->env->jmp_env, 2);
  }
  else {
	log_msg((LOG_TRACE_LEVEL, "No acks needed"));
	result->value.token = T_INTEGER;
	result->value.val.intval = 1;
  }

  return(0);
}
