cb_launch_entry(GtkWidget *widget, gpointer data)
	{
	if (GPOINTER_TO_INT(data) == 0)
		gkrellm_apply_launcher(&mem_launch_entry, &mem_tooltip_entry,
					mem.panel, &mem.launch, gkrellm_launch_button_cb);
	else
		gkrellm_apply_launcher(&swap_launch_entry, &swap_tooltip_entry,
					swap.panel, &swap.launch, gkrellm_launch_button_cb);
	}
