popup_all_resv(GtkTreeModel *model, GtkTreeIter *iter, int id)
{
	char *name = NULL;
	char title[100];
	ListIterator itr = NULL;
	popup_info_t *popup_win = NULL;
	GError *error = NULL;

	gtk_tree_model_get(model, iter, SORTID_NAME, &name, -1);

	switch(id) {
	case PART_PAGE:
		snprintf(title, 100, "Partition(s) with reservation %s", name);
		break;
	case JOB_PAGE:
		snprintf(title, 100, "Job(s) in reservation %s", name);
		break;
	case NODE_PAGE:
		if (cluster_flags & CLUSTER_FLAG_BG)
			snprintf(title, 100,
				 "Midplane(s) in reservation %s",
				 name);
		else
			snprintf(title, 100, "Node(s) in reservation %s ",
				 name);
		break;
	case BLOCK_PAGE:
		snprintf(title, 100, "Block(s) in reservation %s", name);
		break;
	case SUBMIT_PAGE:
		snprintf(title, 100, "Submit job in reservation %s", name);
		break;
	case INFO_PAGE:
		snprintf(title, 100, "Full info for reservation %s", name);
		break;
	default:
		g_print("resv got %d\n", id);
	}

	itr = list_iterator_create(popup_list);
	while ((popup_win = list_next(itr))) {
		if (popup_win->spec_info)
			if (!strcmp(popup_win->spec_info->title, title)) {
				break;
			}
	}
	list_iterator_destroy(itr);

	if (!popup_win) {
		if (id == INFO_PAGE)
			popup_win = create_popup_info(id, RESV_PAGE, title);
		else
			popup_win = create_popup_info(RESV_PAGE, id, title);
	} else {
		g_free(name);
		gtk_window_present(GTK_WINDOW(popup_win->popup));
		return;
	}


	popup_win->model = model;
	popup_win->iter = *iter;
	popup_win->node_inx_id = SORTID_NODE_INX;

	switch(id) {
	case JOB_PAGE:
	case INFO_PAGE:
		popup_win->spec_info->search_info->gchar_data = name;

		break;
	case BLOCK_PAGE:
	case NODE_PAGE:
	case PART_PAGE:
		g_free(name);
		gtk_tree_model_get(model, iter, SORTID_NODELIST, &name, -1);
		popup_win->spec_info->search_info->gchar_data = name;
		popup_win->spec_info->search_info->search_type =
			SEARCH_NODE_NAME;

		break;
	case SUBMIT_PAGE:
		break;
	default:
		g_print("resv got unknown type %d\n", id);
	}
	if (!sview_thread_new((gpointer)popup_thr, popup_win, FALSE, &error)) {
		g_printerr ("Failed to create resv popup thread: %s\n",
			    error->message);
		return;
	}
}
