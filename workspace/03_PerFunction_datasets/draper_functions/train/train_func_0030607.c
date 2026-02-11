FetchStorage(struct worker *wrk, ssize_t sz)
{
	ssize_t l;
	struct storage *st;
	struct object *obj;

	obj = wrk->busyobj->fetch_obj;
	CHECK_OBJ_NOTNULL(obj, OBJECT_MAGIC);
	st = VTAILQ_LAST(&obj->store, storagehead);
	if (st != NULL && st->len < st->space)
		return (st);

	l = fetchfrag;
	if (l == 0)
		l = sz;
	if (l == 0)
		l = cache_param->fetch_chunksize;
	st = STV_alloc(wrk, l);
	if (st == NULL) {
		(void)FetchError(wrk, "Could not get storage");
		return (NULL);
	}
	AZ(st->len);
	VTAILQ_INSERT_TAIL(&obj->store, st, list);
	return (st);
}
