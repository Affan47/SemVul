bfa_fruvpd_update(struct bfa_fru_s *fru, void *buf, u32 len, u32 offset,
		  bfa_cb_fru_t cbfn, void *cbarg, u8 trfr_cmpl)
{
	bfa_trc(fru, BFI_FRUVPD_H2I_WRITE_REQ);
	bfa_trc(fru, len);
	bfa_trc(fru, offset);

	if (fru->ioc->asic_gen != BFI_ASIC_GEN_CT2 &&
		fru->ioc->attr->card_type != BFA_MFG_TYPE_CHINOOK2)
		return BFA_STATUS_FRU_NOT_PRESENT;

	if (fru->ioc->attr->card_type != BFA_MFG_TYPE_CHINOOK)
		return BFA_STATUS_CMD_NOTSUPP;

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
	fru->trfr_cmpl = trfr_cmpl;

	bfa_fru_write_send(fru, BFI_FRUVPD_H2I_WRITE_REQ);

	return BFA_STATUS_OK;
}
