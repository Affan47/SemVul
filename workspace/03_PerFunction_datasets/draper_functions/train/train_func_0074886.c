cb_emit_set_true (cb_tree l)
{
	cb_tree		x;
	struct cb_field *f;
	cb_tree		ref;
	cb_tree		val;

	for (; l; l = CB_CHAIN (l)) {
		x = CB_VALUE (l);
		if (x == cb_error_node) {
			return;
		}
		if (!(CB_REFERENCE_P (x) && CB_FIELD_P(CB_REFERENCE(x)->value))
		     && !CB_FIELD_P (x)) {
			cb_error_x (x, _("Invalid SET statement"));
			return;
		}
		f = cb_field (x);
		if (f->level != 88) {
			cb_error_x (x, _("Invalid SET statement"));
			return;
		}
		ref = cb_build_field_reference (f->parent, x);
		val = CB_VALUE (f->values);
		if (CB_PAIR_P (val)) {
			val = CB_PAIR_X (val);
		}
		cb_emit (cb_build_move (val, ref));
	}
}
