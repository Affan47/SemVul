cb_build_length_1 (cb_tree x)
{
	struct cb_field *f;
	cb_tree		e;
	cb_tree		size;

	f = CB_FIELD (cb_ref (x));

	if (cb_field_variable_size (f) == NULL) {

		return cb_int (cb_field_size (x));
	} else {

		e = NULL;
		for (f = f->children; f; f = f->sister) {
			size = cb_build_length_1 (cb_build_field_reference (f, x));
			if (f->occurs_depending) {
				size = cb_build_binary_op (size, '*', f->occurs_depending);
			} else if (f->occurs_max > 1) {
				size = cb_build_binary_op (size, '*', cb_int (f->occurs_max));
			}
			e = e ? cb_build_binary_op (e, '+', size) : size;
		}
		return e;
	}
}
