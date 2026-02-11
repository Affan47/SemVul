bfad_iocmd_qos(struct bfad_s *bfad, void *cmd, unsigned int v_cmd)
{
	struct bfa_bsg_gen_s *iocmd = (struct bfa_bsg_gen_s *)cmd;
	struct bfa_fcport_s *fcport = BFA_FCPORT_MOD(&bfad->bfa);
	unsigned long	flags;

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	if (bfa_ioc_get_type(&bfad->bfa.ioc) == BFA_IOC_TYPE_FC) {
		if ((fcport->cfg.topology == BFA_PORT_TOPOLOGY_LOOP) &&
		(fcport->topology == BFA_PORT_TOPOLOGY_LOOP))
			iocmd->status = BFA_STATUS_TOPOLOGY_LOOP;
		else {
			if (v_cmd == IOCMD_QOS_ENABLE)
				fcport->cfg.qos_enabled = BFA_TRUE;
			else if (v_cmd == IOCMD_QOS_DISABLE) {
				fcport->cfg.qos_enabled = BFA_FALSE;
				fcport->cfg.qos_bw.high = BFA_QOS_BW_HIGH;
				fcport->cfg.qos_bw.med = BFA_QOS_BW_MED;
				fcport->cfg.qos_bw.low = BFA_QOS_BW_LOW;
			}
		}
	}
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);

	return 0;
}
