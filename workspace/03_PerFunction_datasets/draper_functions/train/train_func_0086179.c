marshal_alloc(struct gc_l *pointers, size_t len, void *orig)
{
	struct gc *gpointer = NULL;

	void *result = calloc(1, len);
	if (!result) return NULL;
	if ((gpointer = (struct gc *)calloc(1,
		    sizeof(struct gc))) == NULL) {
		free(result);
		return NULL;
	}
	gpointer->pointer = result;
	gpointer->orig = orig;
	TAILQ_INSERT_TAIL(pointers, gpointer, next);
	return result;
}
