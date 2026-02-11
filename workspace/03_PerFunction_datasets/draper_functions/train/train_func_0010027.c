bfa_fcs_vport_online(struct bfa_fcs_vport_s *vport)
{
	vport->vport_stats.fab_online++;
	if (bfa_fcs_fabric_npiv_capable(__vport_fabric(vport)))
		bfa_sm_send_event(vport, BFA_FCS_VPORT_SM_ONLINE);
	else
		vport->vport_stats.fab_no_npiv++;
}
