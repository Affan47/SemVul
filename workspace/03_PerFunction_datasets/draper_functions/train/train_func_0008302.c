dbmnycmp(DBPROCESS * dbproc, DBMONEY * m1, DBMONEY * m2)
{
	tdsdump_log(TDS_DBG_FUNC, "dbmnycmp(%p, %p, %p)\n", dbproc, m1, m2);
	CHECK_PARAMETER(dbproc, SYBENULL, 0);
	CHECK_NULP(m1, "dbmnycmp", 2, 0);
	CHECK_NULP(m2, "dbmnycmp", 3, 0);

	if (m1->mnyhigh < m2->mnyhigh) {
		return -1;
	}
	if (m1->mnyhigh > m2->mnyhigh) {
		return 1;
	}
	if (m1->mnylow < m2->mnylow) {
		return -1;
	}
	if (m1->mnylow > m2->mnylow) {
		return 1;
	}
	return 0;
}
