oper_reshufle (GelETree *n, int oper)
{
	gboolean shuffled = FALSE;


	if (n->op.oper == oper) {
		GelETree *l, *r;

		GEL_GET_LR (n, l, r);


		if (r->type == GEL_VALUE_NODE &&
		    l->type != GEL_VALUE_NODE) {
			n->op.args = r;
			r->any.next = l;
			l->any.next = NULL;

			shuffled = TRUE;

			GEL_GET_LR (n, l, r);
		}


		if (r->type == GEL_OPERATOR_NODE &&
		    r->op.oper == oper) {
			GelETree *a, *b, *c;
			a = l;
			b = r->op.args;
			c = r->op.args->any.next;

			if ( ! (a->type == GEL_VALUE_NODE &&
				b->type != GEL_VALUE_NODE &&
				c->type != GEL_VALUE_NODE)) {
				r->op.args = NULL;
				gel_freetree (r);

				GEL_GET_NEW_NODE (l);
				l->type = GEL_OPERATOR_NODE;
				l->op.oper = oper;
				l->op.nargs = 2;
				l->op.args = a;
				a->any.next = b;
				b->any.next = NULL;

				n->op.args = l;
				l->any.next = c;
				c->any.next = NULL;

				shuffled = TRUE;

				GEL_GET_LR (n, l, r);
			}
		}


		if (l->type == GEL_OPERATOR_NODE &&
		    l->op.oper == oper) {
			GelETree *a, *b, *c;
			a = l->op.args;
			b = l->op.args->any.next;
			c = r;

			if (a->type == GEL_VALUE_NODE &&
			    b->type != GEL_VALUE_NODE &&
			    c->type != GEL_VALUE_NODE) {
				l->op.args = NULL;
				gel_freetree (l);

				GEL_GET_NEW_NODE (r);
				r->type = GEL_OPERATOR_NODE;
				r->op.oper = oper;
				r->op.nargs = 2;
				r->op.args = b;
				b->any.next = c;
				c->any.next = NULL;

				n->op.args = a;
				a->any.next = r;
				r->any.next = NULL;

				shuffled = TRUE;


			}
		}
	}
	return shuffled;
}
