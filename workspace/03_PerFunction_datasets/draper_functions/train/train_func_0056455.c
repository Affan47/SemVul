spc_pr_reserve(int host_no, struct scsi_cmd *cmd)
{
	uint16_t asc = ASC_INVALID_FIELD_IN_CDB;
	uint8_t key = ILLEGAL_REQUEST;
	uint8_t pr_scope, pr_type;
	uint8_t *buf;
	uint64_t res_key, sa_res_key;
	int ret;
	struct registration *reg, *holder;

	ret = check_pr_out_basic_parameter(cmd);
	if (ret)
		goto sense;

	pr_scope = (cmd->scb[2] & 0xf0) >> 4;
	pr_type = cmd->scb[2] & 0x0f;

	buf = scsi_get_out_buffer(cmd);

	res_key = get_unaligned_be64(buf);
	sa_res_key = get_unaligned_be64(buf + 8);

	switch (pr_type) {
	case PR_TYPE_WRITE_EXCLUSIVE:
	case PR_TYPE_EXCLUSIVE_ACCESS:
	case PR_TYPE_WRITE_EXCLUSIVE_REGONLY:
	case PR_TYPE_EXCLUSIVE_ACCESS_REGONLY:
	case PR_TYPE_WRITE_EXCLUSIVE_ALLREG:
	case PR_TYPE_EXCLUSIVE_ACCESS_ALLREG:
		break;
	default:
		goto sense;
	}

	if (pr_scope != PR_LU_SCOPE)
		goto sense;

	reg = lookup_registration_by_nexus(cmd->dev, cmd->it_nexus);
	if (!reg)
		return SAM_STAT_RESERVATION_CONFLICT;

	holder = cmd->dev->pr_holder;
	if (holder) {
		if (!is_pr_holder(cmd->dev, reg))
			return SAM_STAT_RESERVATION_CONFLICT;

		if (holder->pr_type != pr_type ||
		    holder->pr_scope != pr_scope)
			return SAM_STAT_RESERVATION_CONFLICT;

		return SAM_STAT_GOOD;
	}

	reg->pr_scope = pr_scope;
	reg->pr_type = pr_type;
	cmd->dev->pr_holder = reg;

	return SAM_STAT_GOOD;
sense:
	scsi_set_in_resid_by_actual(cmd, 0);
	sense_data_build(cmd, key, asc);
	return SAM_STAT_CHECK_CONDITION;
}
