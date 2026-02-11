solver_add_scenario (SolverState *state, GnmSolverResult *res, gchar const *name)
{
	GnmSolverParameters *param = state->sheet->solver_parameters;
	GnmValue const *vinput;
	GnmScenario *sc;
	GnmSheetRange sr;
	WorkbookControl *wbc = WORKBOOK_CONTROL (state->wbcg);

	vinput = gnm_solver_param_get_input (param);
	gnm_sheet_range_from_value (&sr, vinput);

	sc = gnm_sheet_scenario_new (param->sheet, name);
	switch (res->quality) {
	case GNM_SOLVER_RESULT_OPTIMAL:
		gnm_scenario_set_comment
			(sc, _("Optimal solution created by solver.\n"));
		break;
	case GNM_SOLVER_RESULT_FEASIBLE:
		gnm_scenario_set_comment
			(sc, _("Feasible solution created by solver.\n"));
		break;
	default:
		break;
	}
	gnm_scenario_add_area (sc, &sr);

	cmd_scenario_add (wbc, sc, sc->sheet);
}
