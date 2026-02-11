constraint_fill (GnmSolverConstraint *c, SolverState *state)
{
	Sheet *sheet = state->sheet;

	c->type = gtk_combo_box_get_active (state->type_combo);

	gnm_solver_constraint_set_lhs
		(c,
		 gnm_expr_entry_parse_as_value (state->lhs.entry, sheet));

	gnm_solver_constraint_set_rhs
		(c,
		 gnm_solver_constraint_has_rhs (c)
		 ? gnm_expr_entry_parse_as_value (state->rhs.entry, sheet)
		 : NULL);
}
