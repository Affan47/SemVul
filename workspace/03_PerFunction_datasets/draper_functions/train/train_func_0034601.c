qla8044_poll_wait_ipmdio_bus_idle(struct scsi_qla_host *vha,
	uint32_t addr1, uint32_t addr2, uint32_t addr3, uint32_t mask)
{
	unsigned long timeout;
	uint32_t temp;


	timeout = jiffies + msecs_to_jiffies(TIMEOUT_100_MS);
	do {
		temp = qla8044_ipmdio_rd_reg(vha, addr1, addr3, mask, addr2);
		if ((temp & 0x1) != 1)
			break;
		if (time_after_eq(jiffies, timeout)) {
			ql_log(ql_log_warn, vha, 0xb152,
			    "Error in processing mdiobus idle\n");
			return -1;
		}
	} while (1);

	return 0;
}
