spc_pr_register(int host_no, struct scsi_cmd *cmd)
{
	uint8_t force, key = ILLEGAL_REQUEST;
	uint16_t asc = ASC_INVALID_FIELD_IN_CDB;
	uint64_t res_key, sa_res_key;
	int ret;
	uint8_t *buf;
	struct registration *reg;

	force = ((cmd->scb[1] & 0x1f) == PR_OUT_REGISTER_AND_IGNORE_EXISTING_KEY);

	ret = check_pr_out_basic_parameter(cmd);
	if (ret)
		goto sense;

	buf = scsi_get_out_buffer(cmd);

	res_key = get_unaligned_be64(buf);
	sa_res_key = get_unaligned_be64(buf + 8);

	reg = lookup_registration_by_nexus(cmd->dev, cmd->it_nexus);
	if (reg) {
		if (force || reg->key == res_key) {
			if (sa_res_key)
				reg->key = sa_res_key;
			else
				__unregister(cmd->dev, reg);
		} else
			return SAM_STAT_RESERVATION_CONFLICT;
	} else {
		if (force || !res_key) {
			if (sa_res_key) {
				reg = zalloc(sizeof(*reg));
				if (!reg) {
					key = ILLEGAL_REQUEST;
					asc = ASC_INSUFFICENT_REGISTRATION_RESOURCES;
					goto sense;
				}

				reg->key = sa_res_key;
				reg->nexus_id = cmd->cmd_itn_id;
				reg->ctime = cmd->it_nexus->ctime;
				list_add_tail(&reg->registration_siblings,
					      &cmd->dev->registration_list);
			} else
				;
		} else
			return SAM_STAT_RESERVATION_CONFLICT;
	}

	cmd->dev->prgeneration++;

	return SAM_STAT_GOOD;
sense:
	scsi_set_in_resid_by_actual(cmd, 0);
	sense_data_build(cmd, key, asc);
	return SAM_STAT_CHECK_CONDITION;
}
