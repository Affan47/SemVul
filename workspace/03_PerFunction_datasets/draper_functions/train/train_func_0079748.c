gkrellm_chart_show(GkrellmChart *cp, gboolean show_panel)
	{
	gint	h_spacers = 0;

	if (!cp || cp->shown)
		return;

	if (cp->top_spacer.image)
		h_spacers = cp->top_spacer.height;
	if (cp->bottom_spacer.image)
		h_spacers += cp->bottom_spacer.height;

	gtk_widget_show(cp->box);
	gkrellm_freeze_side_frame_packing();
	if (show_panel)
		gkrellm_panel_show(cp->panel);
	cp->shown = TRUE;
	gkrellm_monitor_height_adjust(cp->h + h_spacers);
	gkrellm_thaw_side_frame_packing();
	}
