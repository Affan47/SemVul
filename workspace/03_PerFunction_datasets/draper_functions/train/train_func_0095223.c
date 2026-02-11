spc_access_check(struct scsi_cmd *cmd)
{
	unsigned char op = cmd->scb[0];
	uint8_t bits;
	uint8_t pr_type;
	struct registration *reg;
	int conflict = 0;

	if (!cmd->dev->pr_holder)
		return 0;

	reg = lookup_registration_by_nexus(cmd->dev, cmd->it_nexus);

	if (reg && is_pr_holder(cmd->dev, reg))
		return 0;

	pr_type = cmd->dev->pr_holder->pr_type;
	bits = cmd->dev->dev_type_template.ops[op].pr_conflict_bits;

	if (pr_type == PR_TYPE_WRITE_EXCLUSIVE ||
	    pr_type == PR_TYPE_EXCLUSIVE_ACCESS)
		conflict = bits & (PR_WE_FA|PR_EA_FA);
	else {
		if (reg)
			conflict = bits & PR_RR_FR;
		else {
			if (pr_type == PR_TYPE_WRITE_EXCLUSIVE_REGONLY ||
			    pr_type == PR_TYPE_WRITE_EXCLUSIVE_ALLREG)
				conflict = bits & PR_WE_FN;
			else
				conflict = bits & PR_EA_FN;
		}
	}

	return conflict;
}
