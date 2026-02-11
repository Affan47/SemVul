VSM_find_alloc(struct VSM_data *vd, const char *class, const char *type, const char *ident)
{
	struct VSM_chunk *sha;

	CHECK_OBJ_NOTNULL(vd, VSM_MAGIC);
	AN(vd->VSM_head);
	VSM_FOREACH(sha, vd) {
		CHECK_OBJ_NOTNULL(sha, VSM_CHUNK_MAGIC);
		if (strcmp(sha->class, class))
			continue;
		if (type != NULL && strcmp(sha->type, type))
			continue;
		if (ident != NULL && strcmp(sha->ident, ident))
			continue;
		return (sha);
	}
	return (NULL);
}
