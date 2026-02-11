core_alua_update_tpg_secondary_metadata(struct se_lun *lun)
{
	struct se_portal_group *se_tpg = lun->lun_tpg;
	unsigned char *md_buf;
	char path[ALUA_METADATA_PATH_LEN], wwn[ALUA_SECONDARY_METADATA_WWN_LEN];
	int len, rc;

	mutex_lock(&lun->lun_tg_pt_md_mutex);

	md_buf = kzalloc(ALUA_MD_BUF_LEN, GFP_KERNEL);
	if (!md_buf) {
		pr_err("Unable to allocate buf for ALUA metadata\n");
		rc = -ENOMEM;
		goto out_unlock;
	}

	memset(path, 0, ALUA_METADATA_PATH_LEN);
	memset(wwn, 0, ALUA_SECONDARY_METADATA_WWN_LEN);

	len = snprintf(wwn, ALUA_SECONDARY_METADATA_WWN_LEN, "%s",
			se_tpg->se_tpg_tfo->tpg_get_wwn(se_tpg));

	if (se_tpg->se_tpg_tfo->tpg_get_tag != NULL)
		snprintf(wwn+len, ALUA_SECONDARY_METADATA_WWN_LEN-len, "+%hu",
				se_tpg->se_tpg_tfo->tpg_get_tag(se_tpg));

	len = snprintf(md_buf, ALUA_MD_BUF_LEN, "alua_tg_pt_offline=%d\n"
			"alua_tg_pt_status=0x%02x\n",
			atomic_read(&lun->lun_tg_pt_secondary_offline),
			lun->lun_tg_pt_secondary_stat);

	snprintf(path, ALUA_METADATA_PATH_LEN, "/var/target/alua/%s/%s/lun_%llu",
			se_tpg->se_tpg_tfo->get_fabric_name(), wwn,
			lun->unpacked_lun);

	rc = core_alua_write_tpg_metadata(path, md_buf, len);
	kfree(md_buf);

out_unlock:
	mutex_unlock(&lun->lun_tg_pt_md_mutex);
	return rc;
}
