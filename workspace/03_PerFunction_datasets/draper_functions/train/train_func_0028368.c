dbuf_map(dbuf *dyn, int *length)
{
	if (dyn->head == NULL)
	    {
#ifdef DBUF_TAIL
		dyn->tail = NULL;
#endif
		*length = 0;
		return NULL;
	    }
	*length = DBUFSIZ - dyn->offset;
	if (*length > dyn->length)
		*length = dyn->length;
	return (dyn->head->data + dyn->offset);
}
