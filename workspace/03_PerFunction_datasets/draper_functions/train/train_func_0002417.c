bfa_fcs_is_pbc_vport(struct bfa_fcs_vport_s *vport)
{

	if (vport && (vport->lport.port_cfg.preboot_vp == BFA_TRUE))
		return BFA_TRUE;
	else
		return BFA_FALSE;

}
