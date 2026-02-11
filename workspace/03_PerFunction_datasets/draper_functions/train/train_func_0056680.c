pmsg_new(int prio, const void *buf, int len)
{
	pmsg_t *mb;
	pdata_t *db;

	g_assert(len > 0);
	g_assert(implies(buf, valid_ptr(buf)));

	WALLOC(mb);
	db = pdata_new(len);

	return pmsg_fill(mb, db, prio, FALSE, buf, len);
}
