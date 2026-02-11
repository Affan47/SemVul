bfad_iocmd_vport_clr_stats(struct bfad_s *bfad, void *cmd)
{
	struct bfa_fcs_vport_s *fcs_vport;
	struct bfa_bsg_reset_stats_s *iocmd =
				(struct bfa_bsg_reset_stats_s *)cmd;
	unsigned long	flags;

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	fcs_vport = bfa_fcs_vport_lookup(&bfad->bfa_fcs,
				iocmd->vf_id, iocmd->vpwwn);
	if (fcs_vport == NULL) {
		spin_unlock_irqrestore(&bfad->bfad_lock, flags);
		iocmd->status = BFA_STATUS_UNKNOWN_VWWN;
		goto out;
	}

	memset(&fcs_vport->vport_stats, 0, sizeof(struct bfa_vport_stats_s));
	memset(&fcs_vport->lport.stats, 0, sizeof(struct bfa_lport_stats_s));
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	iocmd->status = BFA_STATUS_OK;
out:
	return 0;
}
