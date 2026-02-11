cmd_vg_add(struct dm_pool *mem, struct dm_list *cmd_vgs,
			  const char *vg_name, const char *vgid,
			  uint32_t flags)
{
	struct cmd_vg *cvl, *ins;

	if (!vg_name && !vgid) {
		log_error("Either vg_name or vgid must be set.");
		return NULL;
	}


	if ((cvl = cmd_vg_lookup(cmd_vgs, vg_name, vgid)))
		return cvl;

	if (!(cvl = dm_pool_zalloc(mem, sizeof(*cvl)))) {
		log_error("Allocation of cmd_vg failed.");
		return NULL;
	}

	if (vg_name && !(cvl->vg_name = dm_pool_strdup(mem, vg_name))) {
		dm_pool_free(mem, cvl);
		log_error("Allocation of vg_name failed.");
		return NULL;
	}

	if (vgid && !(cvl->vgid = dm_pool_strdup(mem, vgid))) {
		dm_pool_free(mem, cvl);
		log_error("Allocation of vgid failed.");
		return NULL;
	}

	cvl->flags = flags;

	if (vg_name)
		dm_list_iterate_items(ins, cmd_vgs)
			if (strcmp(vg_name, ins->vg_name) < 0) {
				cmd_vgs = &ins->list;
				break;
			}

	dm_list_add(cmd_vgs, &cvl->list);

	return cvl;
}
