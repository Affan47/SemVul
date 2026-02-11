bfa_plog_fchdr_and_pl(struct bfa_plog_s *plog, enum bfa_plog_mid mid,
		      enum bfa_plog_eid event, u16 misc, struct fchs_s *fchdr,
		      u32 pld_w0)
{
	struct bfa_plog_rec_s  lp;
	u32	*tmp_int = (u32 *) fchdr;
	u32	ints[BFA_PL_INT_LOG_SZ];

	if (plog->plog_enabled) {
		memset(&lp, 0, sizeof(struct bfa_plog_rec_s));

		ints[0] = tmp_int[0];
		ints[1] = tmp_int[1];
		ints[2] = tmp_int[4];
		ints[3] = pld_w0;

		bfa_plog_intarr(plog, mid, event, misc, ints, 4);
	}
}
