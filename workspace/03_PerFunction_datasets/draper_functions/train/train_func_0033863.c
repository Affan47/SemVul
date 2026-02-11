iks_append (iks *x, const char *name)
{
	iks *y;

	if (!x) return NULL;
	y = iks_new_within (name, x->s);
	if (!y) return NULL;

	if (x->next) {
		x->next->prev = y;
	} else {
		IKS_TAG_LAST_CHILD (x->parent) = y;
	}
	y->next = x->next;
	x->next = y;
	y->parent = x->parent;
	y->prev = x;

	return y;
}
