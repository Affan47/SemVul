ena_com_indirect_table_set(struct ena_com_dev *ena_dev)
{
	struct ena_com_admin_queue *admin_queue = &ena_dev->admin_queue;
	struct ena_rss *rss = &ena_dev->rss;
	struct ena_admin_set_feat_cmd cmd;
	struct ena_admin_set_feat_resp resp;
	int ret;

	if (!ena_com_check_supported_feature_id(
		    ena_dev, ENA_ADMIN_RSS_REDIRECTION_TABLE_CONFIG)) {
		pr_debug("Feature %d isn't supported\n",
			 ENA_ADMIN_RSS_REDIRECTION_TABLE_CONFIG);
		return -EOPNOTSUPP;
	}

	ret = ena_com_ind_tbl_convert_to_device(ena_dev);
	if (ret) {
		pr_err("Failed to convert host indirection table to device table\n");
		return ret;
	}

	memset(&cmd, 0x0, sizeof(cmd));

	cmd.aq_common_descriptor.opcode = ENA_ADMIN_SET_FEATURE;
	cmd.aq_common_descriptor.flags =
		ENA_ADMIN_AQ_COMMON_DESC_CTRL_DATA_INDIRECT_MASK;
	cmd.feat_common.feature_id = ENA_ADMIN_RSS_REDIRECTION_TABLE_CONFIG;
	cmd.u.ind_table.size = rss->tbl_log_size;
	cmd.u.ind_table.inline_index = 0xFFFFFFFF;

	ret = ena_com_mem_addr_set(ena_dev,
				   &cmd.control_buffer.address,
				   rss->rss_ind_tbl_dma_addr);
	if (unlikely(ret)) {
		pr_err("memory address set failed\n");
		return ret;
	}

	cmd.control_buffer.length = (1ULL << rss->tbl_log_size) *
		sizeof(struct ena_admin_rss_ind_table_entry);

	ret = ena_com_execute_admin_command(admin_queue,
					    (struct ena_admin_aq_entry *)&cmd,
					    sizeof(cmd),
					    (struct ena_admin_acq_entry *)&resp,
					    sizeof(resp));

	if (unlikely(ret))
		pr_err("Failed to set indirect table. error: %d\n", ret);

	return ret;
}
