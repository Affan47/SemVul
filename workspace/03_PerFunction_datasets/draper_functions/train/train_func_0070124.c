qla4xxx_sysfs_ddb_add(struct Scsi_Host *shost, const char *buf,
				 int len)
{
	struct scsi_qla_host *ha = to_qla_host(shost);
	struct dev_db_entry *fw_ddb_entry = NULL;
	dma_addr_t fw_ddb_entry_dma;
	struct device *dev;
	uint16_t idx = 0;
	uint16_t max_ddbs = 0;
	uint32_t options = 0;
	uint32_t rval = QLA_ERROR;

	if (strncasecmp(PORTAL_TYPE_IPV4, buf, 4) &&
	    strncasecmp(PORTAL_TYPE_IPV6, buf, 4)) {
		DEBUG2(ql4_printk(KERN_ERR, ha, "%s: Invalid portal type\n",
				  __func__));
		goto exit_ddb_add;
	}

	max_ddbs =  is_qla40XX(ha) ? MAX_PRST_DEV_DB_ENTRIES :
				     MAX_DEV_DB_ENTRIES;

	fw_ddb_entry = dma_alloc_coherent(&ha->pdev->dev, sizeof(*fw_ddb_entry),
					  &fw_ddb_entry_dma, GFP_KERNEL);
	if (!fw_ddb_entry) {
		DEBUG2(ql4_printk(KERN_ERR, ha,
				  "%s: Unable to allocate dma buffer\n",
				  __func__));
		goto exit_ddb_add;
	}

	dev = iscsi_find_flashnode_sess(ha->host, NULL,
					qla4xxx_sysfs_ddb_is_non_persistent);
	if (dev) {
		ql4_printk(KERN_ERR, ha,
			   "%s: A non-persistent entry %s found\n",
			   __func__, dev->kobj.name);
		put_device(dev);
		goto exit_ddb_add;
	}


	for (idx = 2; idx < max_ddbs; idx++) {
		if (qla4xxx_flashdb_by_index(ha, fw_ddb_entry,
					     fw_ddb_entry_dma, idx))
			break;
	}

	if (idx == max_ddbs)
		goto exit_ddb_add;

	if (!strncasecmp("ipv6", buf, 4))
		options |= IPV6_DEFAULT_DDB_ENTRY;

	rval = qla4xxx_get_default_ddb(ha, options, fw_ddb_entry_dma);
	if (rval == QLA_ERROR)
		goto exit_ddb_add;

	rval = qla4xxx_sysfs_ddb_tgt_create(ha, fw_ddb_entry, &idx, 1);

exit_ddb_add:
	if (fw_ddb_entry)
		dma_free_coherent(&ha->pdev->dev, sizeof(*fw_ddb_entry),
				  fw_ddb_entry, fw_ddb_entry_dma);
	if (rval == QLA_SUCCESS)
		return idx;
	else
		return -EIO;
}
