__label_remove(struct aa_label *label, struct aa_label *new)
{
	struct aa_labelset *ls = labels_set(label);
	AA_BUG(!ls);
	AA_BUG(!label);
	AA_BUG(!write_is_locked(&ls->lock));

	if (new)
		__aa_proxy_redirect(label, new);

	if (label_is_stale(label))
		labelstats_dec(stale_intree);
	else
		__label_make_stale(label);

	if (label->flags & FLAG_IN_TREE) {
		labelsetstats_dec(ls, intree);
		rb_erase(&label->node, &ls->root);
		label->flags &= ~FLAG_IN_TREE;
		return true;
	}

	return false;
}
