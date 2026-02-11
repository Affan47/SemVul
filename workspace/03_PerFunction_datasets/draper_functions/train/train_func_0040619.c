__heap_set_heap_regionsize(dbp, npages)
	DB *dbp;
	u_int32_t npages;
{
	HEAP *h;

	DB_ILLEGAL_AFTER_OPEN(dbp, "DB->set_heap_regionsize");
	DB_ILLEGAL_METHOD(dbp, DB_OK_HEAP);

	if (npages == 0) {
		__db_errx(dbp->env, DB_STR("1168", "region size may not be 0"));
		return (EINVAL);
	}

	h = dbp->heap_internal;
	h->region_size = npages;

	return (0);
}
