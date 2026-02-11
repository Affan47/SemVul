bq25890_find_idx(u32 value, enum bq25890_table_ids id)
{
	u8 idx;

	if (id >= TBL_TREG) {
		const u32 *tbl = bq25890_tables[id].lt.tbl;
		u32 tbl_size = bq25890_tables[id].lt.size;

		for (idx = 1; idx < tbl_size && tbl[idx] <= value; idx++)
			;
	} else {
		const struct bq25890_range *rtbl = &bq25890_tables[id].rt;
		u8 rtbl_size;

		rtbl_size = (rtbl->max - rtbl->min) / rtbl->step + 1;

		for (idx = 1;
		     idx < rtbl_size && (idx * rtbl->step + rtbl->min <= value);
		     idx++)
			;
	}

	return idx - 1;
}
