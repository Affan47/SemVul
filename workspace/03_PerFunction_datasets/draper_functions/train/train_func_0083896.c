sysaufs_brs_add(struct super_block *sb, aufs_bindex_t bindex)
{
	int err, i;
	aufs_bindex_t bend;
	struct kobject *kobj;
	struct au_branch *br;
	struct au_brsysfs *br_sysfs;

	dbgaufs_brs_add(sb, bindex);

	if (!sysaufs_brs)
		return;

	kobj = &au_sbi(sb)->si_kobj;
	bend = au_sbend(sb);
	for (; bindex <= bend; bindex++) {
		br = au_sbr(sb, bindex);
		br_sysfs = br->br_sysfs;
		snprintf(br_sysfs[AuBrSysfs_BR].name, sizeof(br_sysfs->name),
			 SysaufsBr_PREFIX "%d", bindex);
		snprintf(br_sysfs[AuBrSysfs_BRID].name, sizeof(br_sysfs->name),
			 SysaufsBrid_PREFIX "%d", bindex);
		for (i = 0; i < ARRAY_SIZE(br->br_sysfs); i++) {
			err = sysfs_create_file(kobj, &br_sysfs->attr);
			if (unlikely(err))
				pr_warn("failed %s under sysfs(%d)\n",
					br_sysfs->name, err);
			br_sysfs++;
		}
	}
}
