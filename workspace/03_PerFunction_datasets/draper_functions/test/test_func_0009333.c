to_unit(struct num *n)
{
	if (!is_distance(*n)) {
		fail("%s^%d is not a distance",
		    n->type == nt_mm ? "mm" : n->type == nt_mil ? "mil" : "?",
		    n->exponent);
		return 0;
	}
	switch (n->type) {
	case nt_mil:
		n->n = mil_to_units(n->n);
		break;
	case nt_mm:
		n->n = mm_to_units(n->n);
		break;
	default:
		abort();
	}
	return 1;
}
