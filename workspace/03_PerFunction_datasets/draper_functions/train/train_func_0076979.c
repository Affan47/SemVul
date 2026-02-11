tds_cursor_deallocated(TDSSOCKET *tds, TDSCURSOR *cursor)
{
	TDSCURSOR *victim = NULL;
	TDSCURSOR *prev = NULL;
	TDSCURSOR *next = NULL;

	tdsdump_log(TDS_DBG_FUNC, "tds_cursor_deallocated() : freeing cursor_id %d\n", cursor->cursor_id);

	if (tds->cur_cursor == cursor) {
		tds_release_cursor(tds, cursor);
		tds->cur_cursor = NULL;
	}

	victim = tds->cursors;

	if (victim == NULL) {
		tdsdump_log(TDS_DBG_FUNC, "tds_cursor_deallocated() : no allocated cursors %d\n", cursor->cursor_id);
		return;
	}

	for (;;) {
		if (victim == cursor)
			break;
		prev = victim;
		victim = victim->next;
		if (victim == NULL) {
			tdsdump_log(TDS_DBG_FUNC, "tds_cursor_deallocated() : cannot find cursor_id %d\n", cursor->cursor_id);
			return;
		}
	}

	tdsdump_log(TDS_DBG_FUNC, "tds_cursor_deallocated() : cursor_id %d found\n", cursor->cursor_id);

	next = victim->next;

	tdsdump_log(TDS_DBG_FUNC, "tds_cursor_deallocated() : relinking list\n");

	if (prev)
		prev->next = next;
	else
		tds->cursors = next;

	tdsdump_log(TDS_DBG_FUNC, "tds_cursor_deallocated() : relinked list\n");

	tds_release_cursor(tds, cursor);
}
