dbuf_init(void)
{
	dbufbuf *dbp;
	int i = 0, nb;

	nb = poolsize / sizeof(dbufbuf);
	freelist = (dbufbuf *)malloc(nb * sizeof(dbufbuf));
	if (!freelist)
		return;
	dbp = freelist;
	for( ; i < (nb - 1); i++, dbp++, istat.is_dbufnow++)
		dbp->next = (dbp + 1);
	dbp->next = NULL;
	istat.is_dbufnow++;
	istat.is_dbuf = istat.is_dbufnow;
}
