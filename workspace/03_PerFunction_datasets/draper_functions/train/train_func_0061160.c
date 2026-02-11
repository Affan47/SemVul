qla2x00_free_sysfs_attr(scsi_qla_host_t *vha, bool stop_beacon)
{
	struct Scsi_Host *host = vha->host;
	struct sysfs_entry *iter;
	struct qla_hw_data *ha = vha->hw;

	for (iter = bin_file_entries; iter->name; iter++) {
		if (iter->is4GBp_only && !IS_FWI2_CAPABLE(ha))
			continue;
		if (iter->is4GBp_only == 2 && !IS_QLA25XX(ha))
			continue;
		if (iter->is4GBp_only == 3 && !(IS_CNA_CAPABLE(vha->hw)))
			continue;
		if (iter->is4GBp_only == 0x27 && !IS_QLA27XX(vha->hw))
			continue;

		sysfs_remove_bin_file(&host->shost_gendev.kobj,
		    iter->attr);
	}

	if (stop_beacon && ha->beacon_blink_led == 1)
		ha->isp_ops->beacon_off(vha);
}
