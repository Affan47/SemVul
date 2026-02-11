__bfa_fcxp_send_cbfn(void *cbarg, bfa_boolean_t complete)
{
	struct bfa_fcxp_s *fcxp = cbarg;

	if (complete) {
		fcxp->send_cbfn(fcxp->caller, fcxp, fcxp->send_cbarg,
				fcxp->rsp_status, fcxp->rsp_len,
				fcxp->residue_len, &fcxp->rsp_fchs);
	} else {
		bfa_fcxp_free(fcxp);
	}
}
