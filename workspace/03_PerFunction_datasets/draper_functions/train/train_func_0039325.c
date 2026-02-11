spc_pr_clear(int host_no, struct scsi_cmd *cmd)
{
	uint16_t asc = ASC_INVALID_FIELD_IN_CDB;
	uint8_t key = ILLEGAL_REQUEST;
	uint8_t *buf;
	uint64_t res_key, sa_res_key;
	int ret;
	struct registration *reg, *holder, *sibling, *n;

	ret = check_pr_out_basic_parameter(cmd);
	if (ret)
		goto sense;

	buf = scsi_get_out_buffer(cmd);

	res_key = get_unaligned_be64(buf);
	sa_res_key = get_unaligned_be64(buf + 8);

	reg = lookup_registration_by_nexus(cmd->dev, cmd->it_nexus);
	if (!reg)
		return SAM_STAT_RESERVATION_CONFLICT;

	if (reg->key != res_key)
		return SAM_STAT_RESERVATION_CONFLICT;

	holder = cmd->dev->pr_holder;
	if (holder) {
		holder->pr_scope = 0;
		holder->pr_type = 0;
		cmd->dev->pr_holder = NULL;
	}

	list_for_each_entry_safe(sibling, n, &cmd->dev->registration_list,
				 registration_siblings) {

		if (sibling != reg)
			ua_sense_add_it_nexus(sibling->nexus_id,
				cmd->dev, ASC_RESERVATIONS_PREEMPTED);
		list_del(&sibling->registration_siblings);
		free(sibling);
	}

	cmd->dev->prgeneration++;
	return SAM_STAT_GOOD;
sense:
	scsi_set_in_resid_by_actual(cmd, 0);
	sense_data_build(cmd, key, asc);
	return SAM_STAT_CHECK_CONDITION;
}
