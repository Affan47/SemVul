cmd_rsv_establish(struct uwb_rc *rc,
			     struct uwb_dbg_cmd_rsv_establish *cmd)
{
	struct uwb_mac_addr macaddr;
	struct uwb_rsv *rsv;
	struct uwb_dev *target;
	int ret;

	memcpy(&macaddr, cmd->target, sizeof(macaddr));
	target = uwb_dev_get_by_macaddr(rc, &macaddr);
	if (target == NULL)
		return -ENODEV;

	rsv = uwb_rsv_create(rc, uwb_dbg_rsv_cb, rc->dbg);
	if (rsv == NULL) {
		uwb_dev_put(target);
		return -ENOMEM;
	}

	rsv->target.type  = UWB_RSV_TARGET_DEV;
	rsv->target.dev   = target;
	rsv->type         = cmd->type;
	rsv->max_mas      = cmd->max_mas;
	rsv->min_mas      = cmd->min_mas;
	rsv->max_interval = cmd->max_interval;

	ret = uwb_rsv_establish(rsv);
	if (ret)
		uwb_rsv_destroy(rsv);
	else {
		spin_lock(&(rc->dbg)->list_lock);
		list_add_tail(&rsv->pal_node, &rc->dbg->rsvs);
		spin_unlock(&(rc->dbg)->list_lock);
	}
	return ret;
}
