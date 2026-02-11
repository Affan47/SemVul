mmc_test_save_transfer_result(struct mmc_test_card *test,
	unsigned int count, unsigned int sectors, struct timespec ts,
	unsigned int rate, unsigned int iops)
{
	struct mmc_test_transfer_result *tr;

	if (!test->gr)
		return;

	tr = kmalloc(sizeof(struct mmc_test_transfer_result), GFP_KERNEL);
	if (!tr)
		return;

	tr->count = count;
	tr->sectors = sectors;
	tr->ts = ts;
	tr->rate = rate;
	tr->iops = iops;

	list_add_tail(&tr->link, &test->gr->tr_lst);
}
