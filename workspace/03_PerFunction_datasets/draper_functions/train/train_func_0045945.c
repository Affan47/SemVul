_lv_is_in_vg(struct volume_group *vg, struct logical_volume *lv)
{
	struct lv_list *lvl;

	dm_list_iterate_items(lvl, &vg->lvs)
		if (lv == lvl->lv)
			 return 1;

	return 0;
}
