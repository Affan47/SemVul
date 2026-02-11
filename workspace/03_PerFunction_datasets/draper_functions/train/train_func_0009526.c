get_reference (GelETree *a, const char *argname, const char *func)
{
	if G_LIKELY (a->type == GEL_OPERATOR_NODE &&
		     a->op.oper == GEL_E_REFERENCE) {
		GelETree *arg = a->op.args;
		g_assert(arg);
		if G_UNLIKELY (arg->type != GEL_IDENTIFIER_NODE ||
			       d_lookup_global (arg->id.id) == NULL) {
			gel_errorout (_("%s: %s not a reference"),
				      func, argname);
			return NULL;
		}
		return d_lookup_global (arg->id.id);
	} else {
		gel_errorout (_("%s: %s not a reference"),
			      func, argname);
		return NULL;
	}
}
