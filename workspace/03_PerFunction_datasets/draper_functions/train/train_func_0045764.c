gnm_solver_set_status (GnmSolver *solver, GnmSolverStatus status)
{
	GnmSolverStatus old_status;

	g_return_if_fail (GNM_IS_SOLVER (solver));

	if (status == solver->status)
		return;

	gnm_solver_set_reason (solver, NULL);

	old_status = solver->status;
	solver->status = status;
	g_object_notify (G_OBJECT (solver), "status");

	if (status == GNM_SOLVER_STATUS_RUNNING)
		g_object_set (G_OBJECT (solver),
			      "starttime", current_time (),
			      "endtime", (double)-1,
			      NULL);
	else if (old_status == GNM_SOLVER_STATUS_RUNNING)
		g_object_set (G_OBJECT (solver),
			      "endtime", current_time (),
			      NULL);
}
