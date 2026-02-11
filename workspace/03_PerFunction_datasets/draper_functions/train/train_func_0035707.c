spc_pr_preempt(int host_no, struct scsi_cmd *cmd)
{
	uint16_t asc = ASC_INVALID_FIELD_IN_CDB;
	uint8_t key = ILLEGAL_REQUEST;
	int ret, abort;
	int res_released = 0, remove_all_reg = 0;
	uint64_t res_key, sa_res_key;
	uint8_t pr_scope, pr_type;
	uint8_t *buf;
	struct registration *holder, *reg, *sibling, *n;

	ret = check_pr_out_basic_parameter(cmd);
	if (ret)
		goto sense;

	abort = ((cmd->scb[1] & 0x1f) == PR_OUT_PREEMPT_AND_ABORT);

	pr_scope = (cmd->scb[2] & 0xf0) >> 4;
	pr_type = cmd->scb[2] & 0x0f;

	buf = scsi_get_out_buffer(cmd);

	res_key = get_unaligned_be64(buf);
	sa_res_key = get_unaligned_be64(buf + 8);

	reg = lookup_registration_by_nexus(cmd->dev, cmd->it_nexus);
	if (!reg)
		return SAM_STAT_RESERVATION_CONFLICT;

	if (reg->key != res_key)
		return SAM_STAT_RESERVATION_CONFLICT;

	if (sa_res_key) {
		ret = check_registration_key_exists(cmd->dev, sa_res_key);
		if (ret)
			return SAM_STAT_RESERVATION_CONFLICT;
	}

	holder = cmd->dev->pr_holder;

	if (holder) {
		if (holder->pr_type == PR_TYPE_WRITE_EXCLUSIVE_ALLREG ||
			holder->pr_type == PR_TYPE_EXCLUSIVE_ACCESS_ALLREG) {

			if (!sa_res_key) {
				if (pr_type != holder->pr_type ||
					pr_scope != holder->pr_scope)
					res_released = 1;
				reg->pr_type = pr_type;
				reg->pr_scope = pr_scope;
				cmd->dev->pr_holder = reg;
				remove_all_reg = 1;
			}
		} else {
			if (holder->key == sa_res_key) {
				if ((pr_type != holder->pr_type) ||
					(pr_scope != holder->pr_scope))
					res_released = 1;
				reg->pr_type = pr_type;
				reg->pr_scope = pr_scope;
				cmd->dev->pr_holder = reg;
			} else {
				if (!sa_res_key)
					goto sense;
			}
		}
	}

	list_for_each_entry_safe(sibling, n, &cmd->dev->registration_list,
					registration_siblings) {
		if (sibling == reg)
			continue;

		if (sibling->key == sa_res_key || remove_all_reg) {
			ua_sense_add_it_nexus(sibling->nexus_id,
				cmd->dev, ASC_RESERVATIONS_PREEMPTED);
			__unregister(cmd->dev, sibling);
		} else {
			if (res_released)
				ua_sense_add_it_nexus(sibling->nexus_id,
				cmd->dev, ASC_RESERVATIONS_RELEASED);
		}
	}

	cmd->dev->prgeneration++;
	return SAM_STAT_GOOD;
sense:
	scsi_set_in_resid_by_actual(cmd, 0);
	sense_data_build(cmd, key, asc);
	return SAM_STAT_CHECK_CONDITION;
}
