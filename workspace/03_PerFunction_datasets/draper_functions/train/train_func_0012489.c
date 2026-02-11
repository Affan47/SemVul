elt_dup(struct elt_s *e)
{
	struct elt_s *e2, *e3, *e4;

	e2 = elt_new();
	if (e2 == 0)
		return e2;
	e2->type = e->type;
	switch (e->type) {
	case VAL:
		e2->u.v = e->u.v;
		break;
	case STR:
		e2->u.s = strdup(e->u.s);
		break;
	case SEQ:
	case BRK:
		e = e->u.e;
		if (e == 0) {
			e2->u.e = 0;
			break;
		}
		e3 = e2->u.e = elt_dup(e);
		if (e3 == 0)
			break;
		for (;;) {
			e = e->next;
			if (e == 0)
				break;
			e4 = elt_dup(e);
			if (e4 == 0)
				break;
			e3->next = e4;
			e3 = e4;
		}
		e3->next = 0;
		break;
	}
	return e2;
}
