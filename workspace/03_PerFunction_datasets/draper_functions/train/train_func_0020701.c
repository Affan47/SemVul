bset_search_tree(struct bset_tree *t,
						const struct bkey *search)
{
	struct bkey *l, *r;
	struct bkey_float *f;
	unsigned inorder, j, n = 1;

	do {
		unsigned p = n << 4;
		p &= ((int) (p - t->size)) >> 31;

		prefetch(&t->tree[p]);

		j = n;
		f = &t->tree[j];


		if (likely(f->exponent != 127))
			n = j * 2 + (((unsigned)
				      (f->mantissa -
				       bfloat_mantissa(search, f))) >> 31);
		else
			n = (bkey_cmp(tree_to_bkey(t, j), search) > 0)
				? j * 2
				: j * 2 + 1;
	} while (n < t->size);

	inorder = to_inorder(j, t);


	if (n & 1) {
		l = cacheline_to_bkey(t, inorder, f->m);

		if (++inorder != t->size) {
			f = &t->tree[inorder_next(j, t->size)];
			r = cacheline_to_bkey(t, inorder, f->m);
		} else
			r = bset_bkey_last(t->data);
	} else {
		r = cacheline_to_bkey(t, inorder, f->m);

		if (--inorder) {
			f = &t->tree[inorder_prev(j, t->size)];
			l = cacheline_to_bkey(t, inorder, f->m);
		} else
			l = t->data->start;
	}

	return (struct bset_search_iter) {l, r};
}
