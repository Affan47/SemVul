cb_list_reverse (cb_tree l)
{
	cb_tree	next;
	cb_tree	last = NULL;

	for (; l; l = next) {
		next = CB_CHAIN (l);
		CB_CHAIN (l) = last;
		last = l;
	}
	return last;
}
