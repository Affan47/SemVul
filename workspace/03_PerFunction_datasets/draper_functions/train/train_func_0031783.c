clock_visibility(void)
	{
	if (clock_enable)
		{
		gkrellm_panel_show(pclock);
		gkrellm_spacers_show(mon_clock);
		}
	else
		{
		gkrellm_panel_hide(pclock);
		gkrellm_spacers_hide(mon_clock);
		}
	}
