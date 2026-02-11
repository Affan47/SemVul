bfad_iocmd_port_get_attr(struct bfad_s *bfad, void *cmd)
{
	struct bfa_bsg_port_attr_s *iocmd = (struct bfa_bsg_port_attr_s *)cmd;
	struct bfa_lport_attr_s	port_attr;
	unsigned long	flags;

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	bfa_fcport_get_attr(&bfad->bfa, &iocmd->attr);
	bfa_fcs_lport_get_attr(&bfad->bfa_fcs.fabric.bport, &port_attr);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);

	if (iocmd->attr.topology != BFA_PORT_TOPOLOGY_NONE)
		iocmd->attr.pid = port_attr.pid;
	else
		iocmd->attr.pid = 0;

	iocmd->attr.port_type = port_attr.port_type;
	iocmd->attr.loopback = port_attr.loopback;
	iocmd->attr.authfail = port_attr.authfail;
	strncpy(iocmd->attr.port_symname.symname,
		port_attr.port_cfg.sym_name.symname,
		sizeof(port_attr.port_cfg.sym_name.symname));

	iocmd->status = BFA_STATUS_OK;
	return 0;
}
