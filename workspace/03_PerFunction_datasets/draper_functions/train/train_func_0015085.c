ubifs_add_to_cat(struct ubifs_info *c, struct ubifs_lprops *lprops,
		      int cat)
{
	switch (cat) {
	case LPROPS_DIRTY:
	case LPROPS_DIRTY_IDX:
	case LPROPS_FREE:
		if (add_to_lpt_heap(c, lprops, cat))
			break;

		cat = LPROPS_UNCAT;

	case LPROPS_UNCAT:
		list_add(&lprops->list, &c->uncat_list);
		break;
	case LPROPS_EMPTY:
		list_add(&lprops->list, &c->empty_list);
		break;
	case LPROPS_FREEABLE:
		list_add(&lprops->list, &c->freeable_list);
		c->freeable_cnt += 1;
		break;
	case LPROPS_FRDI_IDX:
		list_add(&lprops->list, &c->frdi_idx_list);
		break;
	default:
		ubifs_assert(0);
	}

	lprops->flags &= ~LPROPS_CAT_MASK;
	lprops->flags |= cat;
	c->in_a_category_cnt += 1;
	ubifs_assert(c->in_a_category_cnt <= c->main_lebs);
}
