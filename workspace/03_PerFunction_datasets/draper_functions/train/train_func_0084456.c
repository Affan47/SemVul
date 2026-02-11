lgdt3306a_search(struct dvb_frontend *fe)
{
	enum fe_status status = 0;
	int i, ret;


	ret = lgdt3306a_set_parameters(fe);
	if (ret)
		goto error;


	for (i = 20; i > 0; i--) {
		dbg_info(": loop=%d\n", i);
		msleep(50);
		ret = lgdt3306a_read_status(fe, &status);
		if (ret)
			goto error;

		if (status & FE_HAS_LOCK)
			break;
	}


	if (status & FE_HAS_LOCK)
		return DVBFE_ALGO_SEARCH_SUCCESS;
	else
		return DVBFE_ALGO_SEARCH_AGAIN;

error:
	dbg_info("failed (%d)\n", ret);
	return DVBFE_ALGO_SEARCH_ERROR;
}
