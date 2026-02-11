analysis_tool_kaplan_meier_engine (G_GNUC_UNUSED GOCmdContext *gcc, data_analysis_output_t *dao, gpointer specs,
			      analysis_tool_engine_t selector, gpointer result)
{
	analysis_tools_data_kaplan_meier_t *info = specs;
	int multiple;
	int median;

	switch (selector) {
	case TOOL_ENGINE_UPDATE_DESCRIPTOR:
		return (dao_command_descriptor (dao,
						_("Kaplan-Meier (%s)"),
						result)
			== NULL);
	case TOOL_ENGINE_UPDATE_DAO:
		multiple = ((info->group_list == NULL) ? 1 :  g_slist_length (info->group_list));
		median   = (info->median ? (2 + multiple) : 0);
		if (median == 0 && info->logrank_test)
			median = 3;
		dao_adjust (dao, median + 1 + multiple * ((info->std_err ? 4 : 3) + (info->censored ? 1 : 0)),
			    info->base.range_1->v_range.cell.b.row
			    - info->base.range_1->v_range.cell.a.row + 3);
		return FALSE;
	case TOOL_ENGINE_CLEAN_UP:
		value_release (info->range_3);
		info->range_3 = NULL;
		g_slist_foreach (info->group_list, analysis_tool_kaplan_meier_clear_gl_cb, NULL);
		g_slist_free (info->group_list);
		info->group_list = NULL;
		return analysis_tool_generic_b_clean (specs);
	case TOOL_ENGINE_LAST_VALIDITY_CHECK:
		return FALSE;
	case TOOL_ENGINE_PREPARE_OUTPUT_RANGE:
		dao_prepare_output (NULL, dao, _("Kaplan-Meier Estimates"));
		return FALSE;
	case TOOL_ENGINE_FORMAT_OUTPUT_RANGE:
		return dao_format_output (dao, _("Kaplan-Meier Estimates"));
	case TOOL_ENGINE_PERFORM_CALC:
	default:
		return analysis_tool_kaplan_meier_engine_run (dao, specs);
	}
	return TRUE;
}
