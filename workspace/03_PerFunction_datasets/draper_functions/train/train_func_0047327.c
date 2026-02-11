smum_wait_for_register_unequal(struct pp_smumgr *smumgr,
					uint32_t index,
					uint32_t value, uint32_t mask)
{
	uint32_t i;
	uint32_t cur_value;

	if (smumgr == NULL)
		return -EINVAL;

	for (i = 0; i < smumgr->usec_timeout; i++) {
		cur_value = cgs_read_register(smumgr->device,
									index);
		if ((cur_value & mask) != (value & mask))
			break;
		udelay(1);
	}


	if (i == smumgr->usec_timeout)
		return -1;

	return 0;
}
