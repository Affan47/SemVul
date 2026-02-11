varsdb_final(void *key,void *data,va_list ap)
{
	struct vars_info *v = (struct vars_info*)data;

	aFree( v->file );
	aFree( v );
	return 0;
}
