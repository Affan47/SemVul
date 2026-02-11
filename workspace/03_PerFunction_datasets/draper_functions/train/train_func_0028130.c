ena_com_set_aenq_config(struct ena_com_dev *ena_dev, u32 groups_flag)
{
	struct ena_com_admin_queue *admin_queue;
	struct ena_admin_set_feat_cmd cmd;
	struct ena_admin_set_feat_resp resp;
	struct ena_admin_get_feat_resp get_resp;
	int ret;

	ret = ena_com_get_feature(ena_dev, &get_resp, ENA_ADMIN_AENQ_CONFIG);
	if (ret) {
		pr_info("Can't get aenq configuration\n");
		return ret;
	}

	if ((get_resp.u.aenq.supported_groups & groups_flag) != groups_flag) {
		pr_warn("Trying to set unsupported aenq events. supported flag: %x asked flag: %x\n",
			get_resp.u.aenq.supported_groups, groups_flag);
		return -EOPNOTSUPP;
	}

	memset(&cmd, 0x0, sizeof(cmd));
	admin_queue = &ena_dev->admin_queue;

	cmd.aq_common_descriptor.opcode = ENA_ADMIN_SET_FEATURE;
	cmd.aq_common_descriptor.flags = 0;
	cmd.feat_common.feature_id = ENA_ADMIN_AENQ_CONFIG;
	cmd.u.aenq.enabled_groups = groups_flag;

	ret = ena_com_execute_admin_command(admin_queue,
					    (struct ena_admin_aq_entry *)&cmd,
					    sizeof(cmd),
					    (struct ena_admin_acq_entry *)&resp,
					    sizeof(resp));

	if (unlikely(ret))
		pr_err("Failed to config AENQ ret: %d\n", ret);

	return ret;
}
