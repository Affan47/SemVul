bfa_fcs_itnim_create(struct bfa_fcs_rport_s *rport)
{
	struct bfa_fcs_lport_s *port = rport->port;
	struct bfa_fcs_itnim_s *itnim;
	struct bfad_itnim_s   *itnim_drv;


	bfa_fcb_itnim_alloc(port->fcs->bfad, &itnim, &itnim_drv);
	if (itnim == NULL) {
		bfa_trc(port->fcs, rport->pwwn);
		return NULL;
	}


	itnim->rport = rport;
	itnim->fcs = rport->fcs;
	itnim->itnim_drv = itnim_drv;

	itnim->bfa_itnim     = NULL;
	itnim->seq_rec	     = BFA_FALSE;
	itnim->rec_support   = BFA_FALSE;
	itnim->conf_comp     = BFA_FALSE;
	itnim->task_retry_id = BFA_FALSE;


	bfa_sm_set_state(itnim, bfa_fcs_itnim_sm_offline);

	return itnim;
}
