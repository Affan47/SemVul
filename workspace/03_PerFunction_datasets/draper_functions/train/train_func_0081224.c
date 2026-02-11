unsetvar(Var *var)
{
    Toggler *func = NULL;

    if (!(var->flags & VARSET)) return 1;

    if (var->val.type == TYPE_POS) {
        eprintf("%s must be a positive integer, so can not be unset.",
            var->val.name);
        return 0;
    }

    var->flags &= ~VARSET;
    if (var->flags & VAREXPORT) {
	remove_env(var->val.name);
        var->flags &= ~VAREXPORT;
    }

    if (var->func) {
	switch (var->val.type & TYPES_BASIC) {
	case TYPE_STR:     if (var->val.sval->len > 0) func = var->func; break;
	case TYPE_ENUM:
	case TYPE_POS:
	case TYPE_INT:     if (var->val.u.ival != 0) func = var->func; break;
	case TYPE_FLOAT:   if (var->val.u.fval != 0.0) func = var->func; break;
	case TYPE_DECIMAL:
	case TYPE_ATIME:
	case TYPE_DTIME:
	    if (var->val.u.tval.tv_sec || var->val.u.tval.tv_usec)
		func = var->func;
	    break;
	default:
	    internal_error(__FILE__, __LINE__, "bad type %d", var->val.type);
	    break;
	}
    }
    clearval(&var->val);
    if (var->statuses || var->statusfmts || var->statusattrs)
        update_status_field(var, -1);
    if (func)
	(*func)(var);
    freevar(var);

    return 1;
}
