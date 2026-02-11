cmdif_go_bit(struct mtnic *mtnic)
{
	struct mtnic_if_cmd_reg *hcr = mtnic->hcr;
	u32 status;
	int i;

	for (i = 0; i < TBIT_RETRIES; i++) {
		status = be32_to_cpu(readl(&hcr->status_go_opcode));
		if ((status & MTNIC_BC_MASK(MTNIC_MASK_CMD_REG_T_BIT)) ==
		    (mtnic->cmd.tbit << MTNIC_BC_OFF(MTNIC_MASK_CMD_REG_T_BIT))) {

			return status & MTNIC_BC_MASK(MTNIC_MASK_CMD_REG_GO_BIT);
		}
	}

	DBG("Invalid tbit after %d retries!\n", TBIT_RETRIES);
	return -EBUSY;
}
