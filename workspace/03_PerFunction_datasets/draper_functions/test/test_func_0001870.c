bt_dup(prof_bt_t *bt)
{
	prof_bt_t *ret;

	cassert(config_prof);


	ret = (prof_bt_t *)imalloc(QUANTUM_CEILING(sizeof(prof_bt_t)) +
	    (bt->len * sizeof(void *)));
	if (ret == NULL)
		return (NULL);
	ret->vec = (void **)((uintptr_t)ret +
	    QUANTUM_CEILING(sizeof(prof_bt_t)));
	memcpy(ret->vec, bt->vec, bt->len * sizeof(void *));
	ret->len = bt->len;

	return (ret);
}
