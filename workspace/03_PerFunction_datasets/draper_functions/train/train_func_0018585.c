analysis_tool_auto_expression_engine (G_GNUC_UNUSED GOCmdContext *gcc, data_analysis_output_t *dao, gpointer specs,
			      analysis_tool_engine_t selector, gpointer result)
{
	analysis_tools_data_auto_expression_t *info = specs;

	switch (selector) {
	case TOOL_ENGINE_UPDATE_DESCRIPTOR:
		return (dao_command_descriptor
			(dao, _("Auto Expression (%s)"), result)
			== NULL);
	case TOOL_ENGINE_UPDATE_DAO:
		prepare_input_range (&info->base.input, info->base.group_by);
		if (info->below)
			dao_adjust (dao,
				    (info->multiple ? 1 : 0)  + g_slist_length (info->base.input),
				    1);
		else
			dao_adjust (dao, 1,
				    (info->multiple ? 1 : 0)  + g_slist_length (info->base.input));
		return FALSE;
	case TOOL_ENGINE_CLEAN_UP:
		return analysis_tool_auto_expression_engine_clean (specs);
	case TOOL_ENGINE_LAST_VALIDITY_CHECK:
		return FALSE;
	case TOOL_ENGINE_PREPARE_OUTPUT_RANGE:
		dao_prepare_output (NULL, dao, _("Auto Expression"));
		return FALSE;
	case TOOL_ENGINE_FORMAT_OUTPUT_RANGE:
		return dao_format_output (dao, _("Auto Expression"));
	case TOOL_ENGINE_PERFORM_CALC:
	default:
		return analysis_tool_auto_expression_engine_run (dao, specs);
	}
	return TRUE;
}
