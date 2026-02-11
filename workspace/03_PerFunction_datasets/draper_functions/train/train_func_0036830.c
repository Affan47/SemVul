analysis_tool_sign_test_engine (G_GNUC_UNUSED GOCmdContext *gcc, data_analysis_output_t *dao, gpointer specs,
			      analysis_tool_engine_t selector, gpointer result)
{
	analysis_tools_data_sign_test_t *info = specs;

	switch (selector) {
	case TOOL_ENGINE_UPDATE_DESCRIPTOR:
		return (dao_command_descriptor
			(dao, _("Sign Test (%s)"), result)
			== NULL);
	case TOOL_ENGINE_UPDATE_DAO:
		prepare_input_range (&info->base.input, info->base.group_by);
		dao_adjust (dao, 1 + g_slist_length (info->base.input), 8);
		return FALSE;
	case TOOL_ENGINE_CLEAN_UP:
		return analysis_tool_generic_clean (specs);
	case TOOL_ENGINE_LAST_VALIDITY_CHECK:
		return FALSE;
	case TOOL_ENGINE_PREPARE_OUTPUT_RANGE:
		dao_prepare_output (NULL, dao, _("Sign Test"));
		return FALSE;
	case TOOL_ENGINE_FORMAT_OUTPUT_RANGE:
		return dao_format_output (dao, _("Sign Test"));
	case TOOL_ENGINE_PERFORM_CALC:
	default:
		return analysis_tool_sign_test_engine_run (dao, specs);
	}
	return TRUE;
}
