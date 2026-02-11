bfa_fcs_fabric_sm_isolated(struct bfa_fcs_fabric_s *fabric,
			   enum bfa_fcs_fabric_event event)
{
	struct bfad_s *bfad = (struct bfad_s *)fabric->fcs->bfad;
	char	pwwn_ptr[BFA_STRING_32];

	bfa_trc(fabric->fcs, fabric->bport.port_cfg.pwwn);
	bfa_trc(fabric->fcs, event);
	wwn2str(pwwn_ptr, fabric->bport.port_cfg.pwwn);

	BFA_LOG(KERN_INFO, bfad, bfa_log_level,
		"Port is isolated due to VF_ID mismatch. "
		"PWWN: %s Port VF_ID: %04x switch port VF_ID: %04x.",
		pwwn_ptr, fabric->fcs->port_vfid,
		fabric->event_arg.swp_vfid);
}
