__next_ns(struct aa_ns *root, struct aa_ns *ns)
{
	struct aa_ns *parent, *next;

	AA_BUG(!root);
	AA_BUG(!ns);
	AA_BUG(ns != root && !mutex_is_locked(&ns->parent->lock));


	if (!list_empty(&ns->sub_ns)) {
		next = list_first_entry(&ns->sub_ns, typeof(*ns), base.list);
		mutex_lock(&next->lock);
		return next;
	}


	parent = ns->parent;
	while (ns != root) {
		mutex_unlock(&ns->lock);
		next = list_next_entry(ns, base.list);
		if (!list_entry_is_head(next, &parent->sub_ns, base.list)) {
			mutex_lock(&next->lock);
			return next;
		}
		ns = parent;
		parent = parent->parent;
	}

	return NULL;
}
