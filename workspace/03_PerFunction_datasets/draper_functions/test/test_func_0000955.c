db_thread(void *arg)
{
	gfarm_error_t e;
	struct dbq_entry ent;

	for (;;) {
		e = dbq_delete(&dbq, &ent);
		if (e == GFARM_ERR_NO_ERROR) {
			(*ent.func)(ent.data);
		} else if (e == GFARM_ERR_NO_SUCH_OBJECT)
			break;
	}

	return (NULL);
}
