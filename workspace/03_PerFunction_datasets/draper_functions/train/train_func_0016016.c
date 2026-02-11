tds_cursor_close(TDSSOCKET * tds, TDSCURSOR * cursor)
{
	CHECK_TDS_EXTRA(tds);

	if (!cursor)
		return TDS_FAIL;

	tdsdump_log(TDS_DBG_INFO1, "tds_cursor_close() cursor id = %d\n", cursor->cursor_id);

	if (tds_set_state(tds, TDS_QUERYING) != TDS_QUERYING)
		return TDS_FAIL;

	tds_set_cur_cursor(tds, cursor);

	if (IS_TDS50(tds)) {
		tds->out_flag = TDS_NORMAL;
		tds_put_byte(tds, TDS_CURCLOSE_TOKEN);
		tds_put_smallint(tds, 5);
		tds_put_int(tds, cursor->cursor_id);

		if (cursor->status.dealloc == TDS_CURSOR_STATE_REQUESTED) {
			tds_put_byte(tds, 0x01);
			cursor->status.dealloc = TDS_CURSOR_STATE_SENT;
		}
		else
			tds_put_byte(tds, 0x00);

	}
	if (IS_TDS7_PLUS(tds)) {


		tds->out_flag = TDS_RPC;
		START_QUERY;

		if (IS_TDS71_PLUS(tds)) {
			tds_put_smallint(tds, -1);
			tds_put_smallint(tds, TDS_SP_CURSORCLOSE);
		} else {
			tds_put_smallint(tds, 14);
			TDS_PUT_N_AS_UCS2(tds, "sp_cursorclose");
		}


		tds_put_smallint(tds, 2);


		tds_put_byte(tds, 0);
		tds_put_byte(tds, 0);
		tds_put_byte(tds, SYBINTN);
		tds_put_byte(tds, 4);
		tds_put_byte(tds, 4);
		tds_put_int(tds, cursor->cursor_id);
		tds->internal_sp_called = TDS_SP_CURSORCLOSE;
	}
	return tds_query_flush_packet(tds);

}
