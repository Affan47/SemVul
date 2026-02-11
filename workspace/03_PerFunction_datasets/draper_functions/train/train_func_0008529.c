get_value_version(value* v, unsigned ver) {
	assert(!v->is_readonly() && !v->is_rel());
	value *vv = get_value(v->kind, v->select, ver);
	assert(vv);

	if (v->array) {
		vv->array = v->array;
	}

	return vv;
}
