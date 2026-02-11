bfa_ioc_debug_fwcore(struct bfa_ioc_s *ioc, void *buf,
				u32 *offset, int *buflen)
{
	u32 loff;
	int dlen;
	bfa_status_t status;
	u32 smem_len = BFA_IOC_FW_SMEM_SIZE(ioc);

	if (*offset >= smem_len) {
		*offset = *buflen = 0;
		return BFA_STATUS_EINVAL;
	}

	loff = *offset;
	dlen = *buflen;


	if (loff == 0)
		bfa_ioc_fwsync(ioc);

	if ((loff + dlen) >= smem_len)
		dlen = smem_len - loff;

	status = bfa_ioc_smem_read(ioc, buf, loff, dlen);

	if (status != BFA_STATUS_OK) {
		*offset = *buflen = 0;
		return status;
	}

	*offset += dlen;

	if (*offset >= smem_len)
		*offset = 0;

	*buflen = dlen;

	return status;
}
