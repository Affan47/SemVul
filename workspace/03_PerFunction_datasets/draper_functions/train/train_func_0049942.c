draw_proc_extra(void)
	{
	gchar		buf[128];

	if (!proc.chart || !proc.extra_info)
		return;
	format_proc_data(&proc, text_format_locale, buf, sizeof(buf));
	if (!new_text_format)
		gkrellm_chart_reuse_text_format(proc.chart);
	new_text_format = FALSE;
	gkrellm_draw_chart_text(proc.chart, style_id, buf);
	}
