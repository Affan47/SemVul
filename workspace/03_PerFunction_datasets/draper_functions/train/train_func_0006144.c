knot_changesets_get_last(const knot_changesets_t *chs)
{
	if (chs == NULL || EMPTY_LIST(chs->sets)) {
		return NULL;
	}

	return (knot_changeset_t *)(TAIL(chs->sets));
}
