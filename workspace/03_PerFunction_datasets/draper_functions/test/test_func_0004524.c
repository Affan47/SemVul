gst_time_tool_start_clock (GstTimeTool *tool)
{
	GstTimeToolPrivate *priv = GST_TIME_TOOL_GET_PRIVATE (tool);

	if (!priv->clock_timeout) {


		gst_time_tool_update_clock (tool);

		priv->clock_timeout = g_timeout_add (1000, (GSourceFunc) clock_tick, tool);
	}
}
