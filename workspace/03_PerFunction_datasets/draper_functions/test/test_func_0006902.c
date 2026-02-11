mmc_test_multi_xfersize_write(struct mmc_test_card *test)
{
	int ret;

	if (test->card->host->max_blk_count == 1)
		return RESULT_UNSUP_HOST;

	ret = mmc_test_set_blksize(test, 512);
	if (ret)
		return ret;

	return mmc_test_broken_transfer(test, 2, 512, 1);
}
