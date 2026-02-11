tds_cursor_setrows(TDSSOCKET * tds, TDSCURSOR * cursor, int *something_to_send)
{
	CHECK_TDS_EXTRA(tds);

	if (!cursor)
		return TDS_FAIL;

	tdsdump_log(TDS_DBG_INFO1, "tds_cursor_setrows() cursor id = %d\n", cursor->cursor_id);

	if (IS_TDS7_PLUS(tds)) {
		cursor->srv_status &= ~TDS_CUR_ISTAT_DECLARED;
		cursor->srv_status |= TDS_CUR_ISTAT_CLOSED;
		cursor->srv_status |= TDS_CUR_ISTAT_ROWCNT;
	}

	if (IS_TDS50(tds)) {
		if (!*something_to_send) {
			if (tds_set_state(tds, TDS_QUERYING) != TDS_QUERYING)
				return TDS_FAIL;

			tds->out_flag = TDS_NORMAL;
		}
		if (tds->state != TDS_QUERYING  || tds->out_flag != TDS_NORMAL)
			return TDS_FAIL;

		tds_set_cur_cursor(tds, cursor);
		tds_put_byte(tds, TDS_CURINFO_TOKEN);

		TDS_PUT_SMALLINT(tds, 12 + strlen(cursor->cursor_name));


		tds_put_int(tds, 0);
		TDS_PUT_BYTE(tds, strlen(cursor->cursor_name));
		tds_put_n(tds, cursor->cursor_name, (int)strlen(cursor->cursor_name));
		tds_put_byte(tds, 1);
		tds_put_byte(tds, 0x00);
		tds_put_byte(tds, 0x20);
		tds_put_int(tds, cursor->cursor_rows);
		*something_to_send = 1;

	}
	return TDS_SUCCEED;
}
