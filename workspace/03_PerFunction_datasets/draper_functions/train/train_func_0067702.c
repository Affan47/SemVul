niu_init_link(struct niu *np)
{
	struct niu_parent *parent = np->parent;
	int err, ignore;

	if (parent->plat_type == PLAT_TYPE_NIU) {
		err = niu_xcvr_init(np);
		if (err)
			return err;
		msleep(200);
	}
	err = niu_serdes_init(np);
	if (err && !(np->flags & NIU_FLAGS_HOTPLUG_PHY))
		return err;
	msleep(200);
	err = niu_xcvr_init(np);
	if (!err || (np->flags & NIU_FLAGS_HOTPLUG_PHY))
		niu_link_status(np, &ignore);
	return 0;
}
