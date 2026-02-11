bfa_tfru_write(struct bfa_fru_s *fru, void *buf, u32 len, u32 offset,
	       bfa_cb_fru_t cbfn, void *cbarg)
{
	bfa_trc(fru, BFI_TFRU_H2I_WRITE_REQ);
	bfa_trc(fru, len);
	bfa_trc(fru, offset);
	bfa_trc(fru, *((u8 *) buf));

	if (fru->ioc->asic_gen != BFI_ASIC_GEN_CT2)
		return BFA_STATUS_FRU_NOT_PRESENT;

	if (!bfa_ioc_is_operational(fru->ioc))
		return BFA_STATUS_IOC_NON_OP;

	if (fru->op_busy) {
		bfa_trc(fru, fru->op_busy);
		return BFA_STATUS_DEVBUSY;
	}

	fru->op_busy = 1;

	fru->cbfn = cbfn;
	fru->cbarg = cbarg;
	fru->residue = len;
	fru->offset = 0;
	fru->addr_off = offset;
	fru->ubuf = buf;

	bfa_fru_write_send(fru, BFI_TFRU_H2I_WRITE_REQ);

	return BFA_STATUS_OK;
}
