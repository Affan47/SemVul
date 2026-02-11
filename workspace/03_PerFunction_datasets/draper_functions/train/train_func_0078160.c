analysis_tool_ttest_eqvar_engine (G_GNUC_UNUSED GOCmdContext *gcc, data_analysis_output_t *dao, gpointer specs,
				  analysis_tool_engine_t selector, gpointer result)
{
	switch (selector) {
	case TOOL_ENGINE_UPDATE_DESCRIPTOR:
		return (dao_command_descriptor (dao, _("t-Test (%s)"), result)
			== NULL);
	case TOOL_ENGINE_UPDATE_DAO:
		dao_adjust (dao, 3, 13);
		return FALSE;
	case TOOL_ENGINE_CLEAN_UP:
		return analysis_tool_generic_b_clean (specs);
	case TOOL_ENGINE_LAST_VALIDITY_CHECK:
		return FALSE;
	case TOOL_ENGINE_PREPARE_OUTPUT_RANGE:
		dao_prepare_output (NULL, dao, _("t-Test"));
		return FALSE;
	case TOOL_ENGINE_FORMAT_OUTPUT_RANGE:
		return dao_format_output (dao, _("t-Test"));
	case TOOL_ENGINE_PERFORM_CALC:
	default:
		return analysis_tool_ttest_eqvar_engine_run (dao, specs);
	}
	return TRUE;
}
