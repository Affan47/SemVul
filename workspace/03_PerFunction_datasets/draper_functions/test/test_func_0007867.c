charid_db_final(void *key,void *data,va_list ap)
{
	struct charid2nick *p;

	nullpo_retr(0, p = (struct charid2nick *)data);

	if(p->req)
		linkdb_final(&p->req);

	aFree(p);

	return 0;
}
