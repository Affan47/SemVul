procmsg_send_queue(FolderItem *queue, gboolean save_msgs, gchar **errstr)
{
	gint sent = 0, err = 0;
	GSList *list, *elem;
	GSList *sorted_list = NULL;
	GNode *node, *next;

	if (!procmsg_queue_lock(errstr)) {
		main_window_set_menu_sensitive(mainwindow_get_mainwindow());
		toolbar_main_set_sensitive(mainwindow_get_mainwindow());
		return -1;
	}
	inc_lock();
	if (!queue)
		queue = folder_get_default_queue();

	if (queue == NULL) {
		procmsg_queue_unlock();
		inc_unlock();
		return -1;
	}

	main_window_set_menu_sensitive(mainwindow_get_mainwindow());
	toolbar_main_set_sensitive(mainwindow_get_mainwindow());

	folder_item_scan(queue);
	list = folder_item_get_msg_list(queue);


	sorted_list = procmsg_list_sort_by_account(queue, list);

	for (elem = sorted_list; elem != NULL; elem = elem->next) {
		gchar *file;
		MsgInfo *msginfo;

		msginfo = (MsgInfo *)(elem->data);
		if (!MSG_IS_LOCKED(msginfo->flags) && !MSG_IS_DELETED(msginfo->flags)) {
			file = folder_item_fetch_msg(queue, msginfo->msgnum);
			if (file) {
				gboolean queued_removed = FALSE;
				if (procmsg_send_message_queue_full(file,
						!procmsg_is_last_for_account(queue, msginfo, elem),
						errstr, queue, msginfo->msgnum, &queued_removed) < 0) {
					g_warning("Sending queued message %d failed.\n",
						  msginfo->msgnum);
					err++;
				} else {
					sent++;
					if (!queued_removed)
						folder_item_remove_msg(queue, msginfo->msgnum);
				}
				g_free(file);
			}
		}


		procmsg_msginfo_free(msginfo);
	}

	g_slist_free(sorted_list);
	folder_item_scan(queue);

	if (queue->node && queue->node->children) {
		node = queue->node->children;
		while (node != NULL) {
			int res = 0;
			next = node->next;
			send_queue_lock = FALSE;
			res = procmsg_send_queue(FOLDER_ITEM(node->data), save_msgs, errstr);
			send_queue_lock = TRUE;
			if (res < 0)
				err = -res;
			else
				sent += res;
			node = next;
		}
	}
	procmsg_queue_unlock();
	inc_unlock();
	main_window_set_menu_sensitive(mainwindow_get_mainwindow());
	toolbar_main_set_sensitive(mainwindow_get_mainwindow());

	return (err != 0 ? -err : sent);
}
