build_cond_88 (cb_tree x)
{
	struct cb_field	*f;
	cb_tree		l;
	cb_tree		t;
	cb_tree		c1 = NULL;
	cb_tree		c2;

	f = cb_field (x);

	x = cb_build_field_reference (f->parent, x);
	f->parent->count++;


	for (l = f->values; l; l = CB_CHAIN (l)) {
		t = CB_VALUE (l);
		if (CB_PAIR_P (t)) {

			c2 = cb_build_binary_op (cb_build_binary_op (CB_PAIR_X (t), '[', x),
						 '&', cb_build_binary_op (x, '[', CB_PAIR_Y (t)));
		} else {

			c2 = cb_build_binary_op (x, '=', t);
		}
		if (c1 == NULL) {
			c1 = c2;
		} else {
			c1 = cb_build_binary_op (c1, '|', c2);
		}
	}
	return c1;
}
