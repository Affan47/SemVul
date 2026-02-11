dbmap_foreach_remove_trampoline(void *key, void *value, void *arg)
{
	dbmap_datum_t *d = value;
	struct foreach_ctx *ctx = arg;
	bool to_remove;

	to_remove = (*ctx->u.cbr)(key, d, ctx->arg);

	if (to_remove) {
		if (d->data != NULL)
			wfree(d->data, d->len);
		WFREE(d);
	}

	return to_remove;
}
