output_size (cb_tree x)
{
	struct cb_literal	*l;
	struct cb_reference	*r;
	struct cb_field		*f;
	struct cb_field		*p;
	struct cb_field		*q;

	switch (CB_TREE_TAG (x)) {
	case CB_TAG_CONST:
		output ("1");
		break;
	case CB_TAG_LITERAL:
		l = CB_LITERAL (x);
		output ("%d", (int)(l->size + ((l->sign != 0) ? 1 : 0)));
		break;
	case CB_TAG_REFERENCE:
		r = CB_REFERENCE (x);
		f = CB_FIELD (r->value);
		if (r->length) {
			output_integer (r->length);
		} else if (r->offset) {
			output ("%d - ", f->size);
			output_index (r->offset);
		} else {
			p = cb_field_variable_size (f);
			q = f;

again:
			if (p && (r->type == CB_SENDING_OPERAND
			    || !cb_field_subordinate (cb_field (p->occurs_depending), q))) {
				if (p->offset - q->offset > 0) {
					output ("%d + ", p->offset - q->offset);
				}
				if (p->size != 1) {
					output ("%d * ", p->size);
				}
				output_integer (p->occurs_depending);
				q = p;
			} else {
				output ("%d", q->size);
			}

			for (; q != f; q = q->parent) {
				if (q->sister && !q->sister->redefines) {
					q = q->sister;
					p = q->occurs_depending ? q : cb_field_variable_size (q);
					output (" + ");
					goto again;
				}
			}
		}
		break;
	default:
		fprintf (stderr, "Unexpected tree tag %d\n", CB_TREE_TAG (x));
		ABORT ();
	}
}
