bfa_fcdiag_intr(struct bfa_s *bfa, struct bfi_msg_s *msg)
{
	struct bfa_fcdiag_s *fcdiag = BFA_FCDIAG_MOD(bfa);

	switch (msg->mhdr.msg_id) {
	case BFI_DIAG_I2H_LOOPBACK:
		bfa_fcdiag_loopback_comp(fcdiag,
				(struct bfi_diag_lb_rsp_s *) msg);
		break;
	case BFI_DIAG_I2H_QTEST:
		bfa_fcdiag_queuetest_comp(fcdiag, (bfi_diag_qtest_rsp_t *)msg);
		break;
	case BFI_DIAG_I2H_DPORT:
		bfa_dport_req_comp(&fcdiag->dport,
				(struct bfi_diag_dport_rsp_s *)msg);
		break;
	case BFI_DIAG_I2H_DPORT_SCN:
		bfa_dport_scn(&fcdiag->dport,
				(struct bfi_diag_dport_scn_s *)msg);
		break;
	default:
		bfa_trc(fcdiag, msg->mhdr.msg_id);
		WARN_ON(1);
	}
}
