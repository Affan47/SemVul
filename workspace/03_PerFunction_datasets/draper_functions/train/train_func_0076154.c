mmc_test_rw_multiple_sg_len(struct mmc_test_card *test,
				       struct mmc_test_multiple_rw *rw)
{
	int ret = 0;
	int i;

	for (i = 0 ; i < rw->len && ret == 0; i++) {
		ret = mmc_test_rw_multiple(test, rw, 512*1024, rw->size,
					   rw->sg_len[i]);
		if (ret)
			break;
	}
	return ret;
}
