vec_find(struct aa_profile **vec, int n)
{
	struct aa_labelset *ls;
	struct aa_label *label;
	unsigned long flags;

	AA_BUG(!vec);
	AA_BUG(!*vec);
	AA_BUG(n <= 0);

	ls = vec_labelset(vec, n);
	read_lock_irqsave(&ls->lock, flags);
	label = __vec_find(vec, n);
	labelstats_inc(sread);
	read_unlock_irqrestore(&ls->lock, flags);

	return label;
}
