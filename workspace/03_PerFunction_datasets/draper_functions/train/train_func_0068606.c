statusbar_redraw_dirty(void)
{
	GSList *tmp;

	if (statusbar_need_recreate_items) {
		statusbar_need_recreate_items = FALSE;
		statusbars_recreate_items();
	}

	for (tmp = active_statusbar_group->bars; tmp != NULL; tmp = tmp->next) {
		STATUSBAR_REC *rec = tmp->data;

		if (rec->dirty) {
                        statusbar_redraw_needed_items(rec);
			rec->dirty = FALSE;
			rec->dirty_xpos = -1;
		}
	}
}
