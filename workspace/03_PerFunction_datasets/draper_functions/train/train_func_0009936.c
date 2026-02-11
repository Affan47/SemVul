tool_random_engine_run_discrete_last_check (G_GNUC_UNUSED data_analysis_output_t *dao,
					    tools_data_random_t *info,
					    discrete_random_tool_t *param,
					    discrete_random_tool_local_t **continuity)
{
	discrete_random_tool_local_t *data;
	GnmValue *range = param->range;
	gnm_float cumprob = 0;
	int j = 0;
	int i;

	data = *continuity = g_new0 (discrete_random_tool_local_t, 1);
	data->n = range->v_range.cell.b.row - range->v_range.cell.a.row + 1;
	data->cumul_p = g_new (gnm_float, data->n);
	data->values = g_new0 (GnmValue *, data->n);

	for (i = range->v_range.cell.a.row;
	     i <= range->v_range.cell.b.row;
	     i++, j++) {
		GnmValue *v;
		gnm_float thisprob;
		GnmCell *cell = sheet_cell_get (range->v_range.cell.a.sheet,
						range->v_range.cell.a.col + 1, i);

		if (cell == NULL ||
		    (v = cell->value) == NULL ||
		    !VALUE_IS_NUMBER (v)) {
			gnm_cmd_context_error_calc (GO_CMD_CONTEXT (info->wbc),
						    _("The probability input range "
						      "contains a non-numeric value.\n"
						      "All probabilities must be "
						      "non-negative numbers."));
			goto random_tool_discrete_out;
		}
		if ((thisprob = value_get_as_float (v)) < 0) {
			gnm_cmd_context_error_calc (GO_CMD_CONTEXT (info->wbc),
						    _("The probability input range "
						      "contains a negative number.\n"
						      "All probabilities must be "
						      "non-negative!"));
			goto random_tool_discrete_out;
		}

		cumprob += thisprob;
		data->cumul_p[j] = cumprob;

		cell = sheet_cell_get (range->v_range.cell.a.sheet,
				       range->v_range.cell.a.col, i);

		if (cell == NULL || cell->value == NULL) {
			gnm_cmd_context_error_calc (GO_CMD_CONTEXT (info->wbc),
						    _("None of the values in the value "
						      "range may be empty!"));
			goto random_tool_discrete_out;
		}

		data->values[j] = value_dup (cell->value);
	}

	if (cumprob != 0) {

		for (i = 0; i < data->n; i++) {
			data->cumul_p[i] /= cumprob;
		}
		return FALSE;
	}
	gnm_cmd_context_error_calc (GO_CMD_CONTEXT (info->wbc),
				    _("The probabilities may not all be 0!"));

 random_tool_discrete_out:
	tool_random_engine_run_discrete_clear_continuity (continuity);
	return TRUE;
}
