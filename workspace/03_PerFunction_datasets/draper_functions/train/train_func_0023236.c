gst_tool_hide_report_window (GstTool *tool)
{
	if (tool->report_timeout_id) {
		g_source_remove (tool->report_timeout_id);
		tool->report_timeout_id = 0;
	}

	if (tool->report_animate_id) {
		g_source_remove (tool->report_animate_id);
		tool->report_animate_id = 0;
	}

	gtk_widget_hide (tool->report_window);
}
