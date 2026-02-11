draw_inet_extra(InetMon *in)
	{
	gchar	buf[128];

	if (!in->extra_info)
		return;
	format_chart_text(in, text_format_locale, buf, sizeof(buf));
	gkrellm_draw_chart_text(in->chart, style_id, buf);
	}
