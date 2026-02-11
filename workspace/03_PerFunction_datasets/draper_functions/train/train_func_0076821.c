cb_inet_height(GkrellmChartconfig *cf, InetMon *in)
	{
	gint	h;

	h = gkrellm_get_chartconfig_height(cf);
	if (in->chart_minute->h != h)
		gkrellm_set_chart_height(in->chart_minute, h);
	if (in->chart_hour->h != h)
		gkrellm_set_chart_height(in->chart_hour, h);
	}
