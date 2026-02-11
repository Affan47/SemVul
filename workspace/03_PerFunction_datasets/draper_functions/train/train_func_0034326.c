jcnf_get_key(
	jcnf *p,
	int ix,
	char **key,
	jc_type *type,
	unsigned char **data,
	size_t *dataSize,
	char **comment
) {
	jc_error ev;

	if (ix == -1) {
		if (key == NULL || *key == NULL)
			return jc_no_keyname;
		if ((ev = jcnf_locate_key(p, &ix, *key, 1, 0)) != jc_ok)
			return ev;
	} else if (ix < 0 || ix >= p->nkeys)
		return jc_ix_oorange;

	if (key != NULL)
		*key = p->keys[ix]->key;
	if (type != NULL)
		*type = p->keys[ix]->type;
	if (data != NULL)
		*data = p->keys[ix]->data;
	if (dataSize != NULL)
		*dataSize = p->keys[ix]->dataSize;
	if (comment != NULL)
		*comment = p->keys[ix]->cpp_comment;

	return jc_ok;
}
