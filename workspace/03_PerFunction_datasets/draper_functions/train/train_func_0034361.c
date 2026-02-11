cfg_list_length(const cfg_obj_t *obj, isc_boolean_t recurse) {
	const cfg_listelt_t *elt;
	unsigned int count = 0;

	if (obj == NULL || !cfg_obj_islist(obj))
		return (0U);
	for (elt = cfg_list_first(obj);
	     elt != NULL;
	     elt = cfg_list_next(elt)) {
		if (recurse && cfg_obj_islist(elt->obj)) {
			count += cfg_list_length(elt->obj, recurse);
		} else {
			count++;
		}
	}
	return (count);
}
