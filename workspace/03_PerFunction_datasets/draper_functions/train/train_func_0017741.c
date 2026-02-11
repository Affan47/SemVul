mmc_test_rnd_perf(struct mmc_test_card *test, int write, int print,
			     unsigned long sz)
{
	unsigned int dev_addr, cnt, rnd_addr, range1, range2, last_ea = 0, ea;
	unsigned int ssz;
	struct timespec ts1, ts2, ts;
	int ret;

	ssz = sz >> 9;

	rnd_addr = mmc_test_capacity(test->card) / 4;
	range1 = rnd_addr / test->card->pref_erase;
	range2 = range1 / ssz;

	getnstimeofday(&ts1);
	for (cnt = 0; cnt < UINT_MAX; cnt++) {
		getnstimeofday(&ts2);
		ts = timespec_sub(ts2, ts1);
		if (ts.tv_sec >= 10)
			break;
		ea = mmc_test_rnd_num(range1);
		if (ea == last_ea)
			ea -= 1;
		last_ea = ea;
		dev_addr = rnd_addr + test->card->pref_erase * ea +
			   ssz * mmc_test_rnd_num(range2);
		ret = mmc_test_area_io(test, sz, dev_addr, write, 0, 0);
		if (ret)
			return ret;
	}
	if (print)
		mmc_test_print_avg_rate(test, sz, cnt, &ts1, &ts2);
	return 0;
}
