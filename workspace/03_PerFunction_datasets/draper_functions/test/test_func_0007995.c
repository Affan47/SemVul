BAN_Free(struct ban *b)
{

	CHECK_OBJ_NOTNULL(b, BAN_MAGIC);
	AZ(b->refcount);
	assert(VTAILQ_EMPTY(&b->objcore));

	if (b->vsb != NULL)
		VSB_delete(b->vsb);
	if (b->spec != NULL)
		free(b->spec);
	FREE_OBJ(b);
}
