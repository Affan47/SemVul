decimal_expand (cb_tree d, cb_tree x)
{
	struct cb_literal	*l;
	struct cb_field		*f;
	struct cb_binary_op	*p;
	cb_tree			t;

	switch (CB_TREE_TAG (x)) {
	case CB_TAG_CONST:
		if (x == cb_zero) {
			dpush (cb_build_funcall_2 ("cob_decimal_set_int", d, cb_int0));
			current_program->gen_decset = 1;
		} else {
			fprintf (stderr, "Unexpected constant expansion\n");
			ABORT ();
		}
		break;
	case CB_TAG_LITERAL:

		l = CB_LITERAL (x);
		if (l->size < 10 && l->scale == 0) {
			dpush (cb_build_funcall_2 ("cob_decimal_set_int", d, cb_build_cast_integer (x)));
			current_program->gen_decset = 1;
		} else {
			dpush (cb_build_funcall_2 ("cob_decimal_set_field", d, x));
		}
		break;
	case CB_TAG_REFERENCE:

		f = cb_field (x);

		if (CB_EXCEPTION_ENABLE (COB_EC_DATA_INCOMPATIBLE)) {
			if (f->usage == CB_USAGE_DISPLAY || f->usage == CB_USAGE_PACKED) {
				dpush (cb_build_funcall_2 ("cob_check_numeric",
							   x, cb_build_string0 ((ucharptr)(f->name))));
			}
		}

		if (cb_fits_int (x)) {
			if (f->pic->have_sign) {
				dpush (cb_build_funcall_2 ("cob_decimal_set_int", d, cb_build_cast_integer (x)));
				current_program->gen_decset = 1;
			} else {
				dpush (cb_build_funcall_2 ("cob_decimal_set_uint", d, cb_build_cast_integer (x)));
				current_program->gen_udecset = 1;
			}
		} else {
			dpush (cb_build_funcall_2 ("cob_decimal_set_field", d, x));
		}
		break;
	case CB_TAG_BINARY_OP:


		p = CB_BINARY_OP (x);
		t = decimal_alloc ();
		decimal_expand (d, p->x);
		decimal_expand (t, p->y);
		decimal_compute (p->op, d, t);
		decimal_free ();
		break;
	case CB_TAG_INTRINSIC:
		dpush (cb_build_funcall_2 ("cob_decimal_set_field", d, x));
		break;
	default:
		fprintf (stderr, "Unexpected tree tag %d\n", CB_TREE_TAG (x));
		ABORT ();
	}
}
