cmp_connection_check_used(struct cmp_connection *c, bool *used)
{
	__be32 pcr;
	int err;

	err = snd_fw_transaction(
			c->resources.unit, TCODE_READ_QUADLET_REQUEST,
			pcr_address(c), &pcr, 4, 0);
	if (err >= 0)
		*used = !!(pcr & cpu_to_be32(PCR_BCAST_CONN |
					     PCR_P2P_CONN_MASK));

	return err;
}
