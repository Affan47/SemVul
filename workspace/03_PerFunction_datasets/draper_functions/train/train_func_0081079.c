t4_fw_reset(struct adapter *adap, unsigned int mbox, int reset)
{
	struct fw_reset_cmd c;

	memset(&c, 0, sizeof(c));
	INIT_CMD(c, RESET, WRITE);
	c.val = cpu_to_be32(reset);
	return t4_wr_mbox(adap, mbox, &c, sizeof(c), NULL);
}
