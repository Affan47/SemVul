qla8044_poll_wait_for_ready(struct scsi_qla_host *vha, uint32_t addr1,
	uint32_t mask)
{
	unsigned long timeout;
	uint32_t temp;


	timeout = jiffies + msecs_to_jiffies(TIMEOUT_100_MS);
	do {
		qla8044_rd_reg_indirect(vha, addr1, &temp);
		if ((temp & mask) != 0)
			break;
		if (time_after_eq(jiffies, timeout)) {
			ql_log(ql_log_warn, vha, 0xb151,
				"Error in processing rdmdio entry\n");
			return -1;
		}
	} while (1);

	return 0;
}
