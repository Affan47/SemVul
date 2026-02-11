bfa_fcport_send_disable(struct bfa_fcport_s *fcport)
{
	struct bfi_fcport_req_s *m;


	fcport->msgtag++;


	m = bfa_reqq_next(fcport->bfa, BFA_REQQ_PORT);
	if (!m) {
		bfa_reqq_wait(fcport->bfa, BFA_REQQ_PORT,
							&fcport->reqq_wait);
		return BFA_FALSE;
	}

	bfi_h2i_set(m->mh, BFI_MC_FCPORT, BFI_FCPORT_H2I_DISABLE_REQ,
			bfa_fn_lpu(fcport->bfa));
	m->msgtag = fcport->msgtag;


	bfa_reqq_produce(fcport->bfa, BFA_REQQ_PORT, m->mh);

	return BFA_TRUE;
}
