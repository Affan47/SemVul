knot_changesets_create()
{
	knot_changesets_t *ch = NULL;
	int ret = knot_changesets_init(&ch);
	if (ret != KNOT_EOK) {
		return NULL;
	} else {
		return ch;
	}
}
