bfa_fcs_vport_sm_deleting(struct bfa_fcs_vport_s *vport,
			enum bfa_fcs_vport_event event)
{
	bfa_trc(__vport_fcs(vport), __vport_pwwn(vport));
	bfa_trc(__vport_fcs(vport), event);

	switch (event) {
	case BFA_FCS_VPORT_SM_DELETE:
		break;

	case BFA_FCS_VPORT_SM_DELCOMP:
		bfa_sm_set_state(vport, bfa_fcs_vport_sm_logo);
		bfa_fcs_vport_do_logo(vport);
		break;

	case BFA_FCS_VPORT_SM_OFFLINE:
		bfa_sm_set_state(vport, bfa_fcs_vport_sm_cleanup);
		break;

	default:
		bfa_sm_fault(__vport_fcs(vport), event);
	}
}
