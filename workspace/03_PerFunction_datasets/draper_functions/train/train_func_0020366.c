dstrassure(dstr_t *ds, size_t alloc)
{
	if (ds->alloc < alloc) {
		ds->alloc = alloc;
		ds->data = realloc(ds->data, ds->alloc);
	}
}
