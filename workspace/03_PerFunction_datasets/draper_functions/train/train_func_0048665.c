gnm_solver_constraint_as_str (GnmSolverConstraint const *c, Sheet *sheet)
{
	const char * const type_str[] =	{
		"\xe2\x89\xa4" ,
		"\xe2\x89\xa5" ,
		"=",
		N_("Int"),
		N_("Bool")
	};
	const char *type = type_str[c->type];
	gboolean translate = (c->type >= GNM_SOLVER_INTEGER);
	GString *buf = g_string_new (NULL);

	gnm_solver_constraint_side_as_str (c, sheet, buf, TRUE);
	g_string_append_c (buf, ' ');
	g_string_append (buf, translate ? _(type) : type);
	if (gnm_solver_constraint_has_rhs (c)) {
		g_string_append_c (buf, ' ');
		gnm_solver_constraint_side_as_str (c, sheet, buf, FALSE);
	}

	return g_string_free (buf, FALSE);
}
