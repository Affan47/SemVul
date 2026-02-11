getline_make(size_t maxlen)
{
	getline_t *o;

	g_assert(size_is_positive(maxlen));

	WALLOC0(o);
	o->magic = GETLINE_MAGIC;
	o->maxlen = maxlen;
	o->size = MIN(START_LENGTH, maxlen);
	o->line = halloc(o->size);

	return o;
}
