mdb_memo_to_string(MdbHandle *mdb, int start, int size)
{
	guint32 memo_len;
	gint32 row_start, pg_row;
	size_t len;
	void *buf, *pg_buf = mdb->pg_buf;
	char *text = (char *) g_malloc(MDB_BIND_SIZE);

	if (size<MDB_MEMO_OVERHEAD) {
		strcpy(text, "");
		return text;
	}

#if MDB_DEBUG
	buffer_dump(pg_buf, start, MDB_MEMO_OVERHEAD);
#endif


	memo_len = mdb_get_int32(pg_buf, start);

	if (memo_len & 0x80000000) {

		mdb_unicode2ascii(mdb, pg_buf + start + MDB_MEMO_OVERHEAD,
			size - MDB_MEMO_OVERHEAD, text, MDB_BIND_SIZE);
		return text;
	} else if (memo_len & 0x40000000) {

		pg_row = mdb_get_int32(pg_buf, start+4);
#if MDB_DEBUG
		printf("Reading LVAL page %06x\n", pg_row >> 8);
#endif
		if (mdb_find_pg_row(mdb, pg_row, &buf, &row_start, &len)) {
			strcpy(text, "");
			return text;
		}
#if MDB_DEBUG
		printf("row num %d start %d len %d\n",
			pg_row & 0xff, row_start, len);
		buffer_dump(buf, row_start, len);
#endif
		mdb_unicode2ascii(mdb, buf + row_start, len, text, MDB_BIND_SIZE);
		return text;
	} else if ((memo_len & 0xff000000) == 0) {

		guint32 tmpoff = 0;
		char *tmp;

		tmp = (char *) g_malloc(memo_len);
		pg_row = mdb_get_int32(pg_buf, start+4);
		do {
#if MDB_DEBUG
			printf("Reading LVAL page %06x\n", pg_row >> 8);
#endif
			if (mdb_find_pg_row(mdb,pg_row,&buf,&row_start,&len)) {
				g_free(tmp);
				strcpy(text, "");
				return text;
			}
#if MDB_DEBUG
			printf("row num %d start %d len %d\n",
				pg_row & 0xff, row_start, len);
#endif
			if (tmpoff + len - 4 > memo_len) {
				break;
			}
			memcpy(tmp + tmpoff, buf + row_start + 4, len - 4);
			tmpoff += len - 4;
		} while (( pg_row = mdb_get_int32(buf, row_start) ));
		if (tmpoff < memo_len) {
			fprintf(stderr, "Warning: incorrect memo length\n");
		}
		mdb_unicode2ascii(mdb, tmp, tmpoff, text, MDB_BIND_SIZE);
		g_free(tmp);
		return text;
	} else {
		fprintf(stderr, "Unhandled memo field flags = %02x\n", memo_len >> 24);
		strcpy(text, "");
		return text;
	}
}
