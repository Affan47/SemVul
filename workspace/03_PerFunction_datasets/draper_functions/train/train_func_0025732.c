VRT_r_beresp_storage(struct sess *sp)
{
	CHECK_OBJ_NOTNULL(sp, SESS_MAGIC);
	if (sp->wrk->storage_hint != NULL)
		return (sp->wrk->storage_hint);
	else
		return (NULL);
}
