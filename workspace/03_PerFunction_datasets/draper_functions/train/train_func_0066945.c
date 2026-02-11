gnm_nlsolve_start (GnmSolver *sol, WorkbookControl *wbc, GError **err,
		   GnmNlsolve *nl)
{
	gboolean ok = TRUE;

	g_return_val_if_fail (sol->status == GNM_SOLVER_STATUS_PREPARED, FALSE);

	nl->idle_tag = g_idle_add (gnm_nlsolve_idle, nl);
	gnm_solver_set_status (sol, GNM_SOLVER_STATUS_RUNNING);

	return ok;
}
