ubifs_fast_find_frdi_idx(struct ubifs_info *c)
{
	struct ubifs_lprops *lprops;

	ubifs_assert(mutex_is_locked(&c->lp_mutex));

	if (list_empty(&c->frdi_idx_list))
		return NULL;

	lprops = list_entry(c->frdi_idx_list.next, struct ubifs_lprops, list);
	ubifs_assert(!(lprops->flags & LPROPS_TAKEN));
	ubifs_assert((lprops->flags & LPROPS_INDEX));
	ubifs_assert(lprops->free + lprops->dirty == c->leb_size);
	return lprops;
}
