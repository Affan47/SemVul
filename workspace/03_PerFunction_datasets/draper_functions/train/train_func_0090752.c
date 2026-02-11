tx_ut_mset_unref(void)
{
	g_assert(ut_mset != NULL);

	if (0 == --ut_mset_refcnt)
		hevset_free_null(&ut_mset);
}
