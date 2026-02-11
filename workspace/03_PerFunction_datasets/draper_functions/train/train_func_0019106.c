find_lv_in_vg_by_lvid(struct volume_group *vg,
				      const union lvid *lvid)
{
	struct lv_list *lvl;

	dm_list_iterate_items(lvl, &vg->lvs)
		if (!strncmp(lvl->lv->lvid.s, lvid->s, sizeof(*lvid)))
			return lvl;

	return NULL;
}
