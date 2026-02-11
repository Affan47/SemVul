gnm_lpsolve_start_solution (GnmLPSolve *lp)
{
	g_return_val_if_fail (lp->result == NULL, NULL);

	lp->result = g_object_new (GNM_SOLVER_RESULT_TYPE, NULL);
	lp->result->solution = value_new_array_empty
		(range_width (&lp->srinput.range),
		 range_height (&lp->srinput.range));

	return lp->result;
}
