bfad_iocmd_phy_get_stats(struct bfad_s *bfad, void *cmd)
{
	struct bfa_bsg_phy_stats_s *iocmd =
			(struct bfa_bsg_phy_stats_s *)cmd;
	struct bfad_hal_comp fcomp;
	unsigned long	flags;

	init_completion(&fcomp.comp);
	spin_lock_irqsave(&bfad->bfad_lock, flags);
	iocmd->status = bfa_phy_get_stats(BFA_PHY(&bfad->bfa), iocmd->instance,
				&iocmd->stats, bfad_hcb_comp, &fcomp);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	if (iocmd->status != BFA_STATUS_OK)
		goto out;
	wait_for_completion(&fcomp.comp);
	iocmd->status = fcomp.status;
out:
	return 0;
}
