bfad_iocmd_pcifn_bw(struct bfad_s *bfad, void *cmd)
{
	struct bfa_bsg_pcifn_s *iocmd = (struct bfa_bsg_pcifn_s *)cmd;
	struct bfad_hal_comp fcomp;
	unsigned long flags;

	init_completion(&fcomp.comp);
	spin_lock_irqsave(&bfad->bfad_lock, flags);
	iocmd->status = bfa_ablk_pf_update(&bfad->bfa.modules.ablk,
				iocmd->pcifn_id, iocmd->bw_min,
				iocmd->bw_max, bfad_hcb_comp, &fcomp);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	bfa_trc(bfad, iocmd->status);
	if (iocmd->status != BFA_STATUS_OK)
		goto out;

	wait_for_completion(&fcomp.comp);
	iocmd->status = fcomp.status;
	bfa_trc(bfad, iocmd->status);
out:
	return 0;
}
