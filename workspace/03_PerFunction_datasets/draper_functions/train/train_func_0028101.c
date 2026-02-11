backq_car(object x)
{
	int d;

	cs_check(x);

	if (type_of(x) != t_cons) {
		vs_push(x);
		return(QUOTE);
	}
	if (x->c.c_car == siScomma) {
		vs_push(x->c.c_cdr);
		return(EVAL);
	}
	if (x->c.c_car == siScomma_at) {
		vs_push(x->c.c_cdr);
		return(APPEND);
	}
	if (x->c.c_car == siScomma_dot) {
		vs_push(x->c.c_cdr);
		return(NCONC);
	}
	d = backq_cdr(x);
	switch (d) {
	case QUOTE:
		return(QUOTE);

	case EVAL:
		return(EVAL);

	case LIST:
		attach(sLlist);
		break;

	case LISTA:
		attach(sLlistA);
		break;

	case APPEND:
		attach(sLappend);
		break;

	case NCONC:
		attach(sLnconc);
		break;

	default:
		error("backquote botch");
        }
	return(EVAL);
}
