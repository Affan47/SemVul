db_free_rows(db_res_t* _r)
{
	int i;

	if (!_r) {
		LM_ERR("invalid parameter value\n");
		return -1;
	}
	LM_DBG("freeing %d rows\n", RES_ROW_N(_r));

	if (RES_ROWS(_r)) {
		for(i = 0; i < RES_ROW_N(_r); i++)
			db_free_row(&(RES_ROWS(_r)[i]));

		LM_DBG("freeing rows at %p\n", RES_ROWS(_r));
		pkg_free(RES_ROWS(_r));
		RES_ROWS(_r) = NULL;
	}

	RES_ROW_N(_r) = 0;

	return 0;
}
