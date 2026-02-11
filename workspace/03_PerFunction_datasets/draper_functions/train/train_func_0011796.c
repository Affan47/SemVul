remove_lvs_in_vg(struct cmd_context *cmd,
		     struct volume_group *vg,
		     force_t force)
{
	struct dm_list *lst;
	struct lv_list *lvl;

	while ((lst = dm_list_first(&vg->lvs))) {
		lvl = dm_list_item(lst, struct lv_list);
		if (!lv_remove_with_dependencies(cmd, lvl->lv, force, 0))
		    return 0;
	}

	return 1;
}
