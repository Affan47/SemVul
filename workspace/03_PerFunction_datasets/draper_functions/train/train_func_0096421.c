core_tpg_alloc_lun(
	struct se_portal_group *tpg,
	u64 unpacked_lun)
{
	struct se_lun *lun;

	lun = kzalloc(sizeof(*lun), GFP_KERNEL);
	if (!lun) {
		pr_err("Unable to allocate se_lun memory\n");
		return ERR_PTR(-ENOMEM);
	}
	lun->unpacked_lun = unpacked_lun;
	lun->lun_link_magic = SE_LUN_LINK_MAGIC;
	atomic_set(&lun->lun_acl_count, 0);
	init_completion(&lun->lun_ref_comp);
	init_completion(&lun->lun_shutdown_comp);
	INIT_LIST_HEAD(&lun->lun_deve_list);
	INIT_LIST_HEAD(&lun->lun_dev_link);
	atomic_set(&lun->lun_tg_pt_secondary_offline, 0);
	spin_lock_init(&lun->lun_deve_lock);
	mutex_init(&lun->lun_tg_pt_md_mutex);
	INIT_LIST_HEAD(&lun->lun_tg_pt_gp_link);
	spin_lock_init(&lun->lun_tg_pt_gp_lock);
	lun->lun_tpg = tpg;

	return lun;
}
