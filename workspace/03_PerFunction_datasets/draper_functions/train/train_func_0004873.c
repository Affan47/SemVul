cb_dialog_solve_clicked (G_GNUC_UNUSED GtkWidget *button,
			 SolverState *state)
{
	GnmSolverResult *res;
	GnmSolverParameters *param = state->sheet->solver_parameters;
	GError *err = NULL;

	if (state->warning_dialog != NULL) {
		gtk_widget_destroy (state->warning_dialog);
		state->warning_dialog = NULL;
	}

	extract_settings (state);

	if (!gnm_solver_param_valid (param, &err)) {
		GtkWidget *top = gtk_widget_get_toplevel (state->dialog);
		go_gtk_notice_dialog (GTK_WINDOW (top), GTK_MESSAGE_ERROR,
				      "%s", err->message);
		goto out;
	}

	check_for_changed_options (state);

	res = run_solver (state, param);

	gnm_app_recalc ();

	if (res != NULL) {
		if ((res->quality == GNM_SOLVER_RESULT_OPTIMAL ||
		     res->quality == GNM_SOLVER_RESULT_FEASIBLE) &&
		    param->options.add_scenario)
			solver_add_scenario (state, res,
					     param->options.scenario_name);

		g_object_unref (res);
	} else if (err) {
		go_gtk_notice_nonmodal_dialog
			(GTK_WINDOW (state->dialog),
			 &(state->warning_dialog),
			 GTK_MESSAGE_ERROR,
			 "%s", err->message);
	}

 out:
	if (err)
		g_error_free (err);
}
