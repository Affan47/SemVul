chart_destroy_text_run_list(GkrellmChart *cp)
	{
	GList			*list;

	if (!cp || !cp->text_run_list)
		return;
	for (list = cp->text_run_list; list; list = list->next)
		g_free(((GkrellmTextRun *) list->data)->text);
	gkrellm_free_glist_and_data(&cp->text_run_list);
	}
