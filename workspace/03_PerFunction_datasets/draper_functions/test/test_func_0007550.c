stringOf(Expr_t * prog, register Exnode_t * x, int arg, Exdisc_t* disc)
{
    Agobj_t *objp;
    int rv = 0;

    if (arg)
	return 0;

    if (x->type == T_tvtyp) {
	if (!(x->data.constant.value.string =
	    tvtypeToStr (x->data.constant.value.integer)))
	    rv = -1;
    } else {
	objp = INT2PTR(Agobj_t *, x->data.constant.value.integer);
	if (!objp) {
	    exerror("cannot generate name for NULL %s",
		    typeName(prog, x->type));
	    rv = -1;
	}
	else {
	    Gpr_t* state = (Gpr_t *) (disc->user);
	    x->data.constant.value.string = nameOf(prog, objp, state->tmp);
	}
    }
    x->type = STRING;
    return 0;
}
