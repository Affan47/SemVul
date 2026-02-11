cb_validate_78_item (struct cb_field *f)
{
	cb_tree x;

	x = CB_TREE (f);
	if (!f->values) {
		level_require_error (x, "VALUE");
	}

	if (f->pic || f->flag_occurs) {
		level_except_error (x, "VALUE");
	}
	cb_add_78 (f);
	return last_real_field;
}
