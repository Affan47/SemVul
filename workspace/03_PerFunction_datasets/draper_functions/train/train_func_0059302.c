bfad_iocmd_rport_get_addr(struct bfad_s *bfad, void *cmd)
{
	struct bfa_bsg_rport_scsi_addr_s *iocmd =
			(struct bfa_bsg_rport_scsi_addr_s *)cmd;
	struct bfa_fcs_lport_s	*fcs_port;
	struct bfa_fcs_itnim_s	*fcs_itnim;
	struct bfad_itnim_s	*drv_itnim;
	unsigned long	flags;

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	fcs_port = bfa_fcs_lookup_port(&bfad->bfa_fcs,
				iocmd->vf_id, iocmd->pwwn);
	if (fcs_port == NULL) {
		bfa_trc(bfad, 0);
		spin_unlock_irqrestore(&bfad->bfad_lock, flags);
		iocmd->status = BFA_STATUS_UNKNOWN_LWWN;
		goto out;
	}

	fcs_itnim = bfa_fcs_itnim_lookup(fcs_port, iocmd->rpwwn);
	if (fcs_itnim == NULL) {
		bfa_trc(bfad, 0);
		spin_unlock_irqrestore(&bfad->bfad_lock, flags);
		iocmd->status = BFA_STATUS_UNKNOWN_RWWN;
		goto out;
	}

	drv_itnim = fcs_itnim->itnim_drv;

	if (drv_itnim && drv_itnim->im_port)
		iocmd->host = drv_itnim->im_port->shost->host_no;
	else {
		bfa_trc(bfad, 0);
		spin_unlock_irqrestore(&bfad->bfad_lock, flags);
		iocmd->status = BFA_STATUS_UNKNOWN_RWWN;
		goto out;
	}

	iocmd->target = drv_itnim->scsi_tgt_id;
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);

	iocmd->bus = 0;
	iocmd->lun = 0;
	iocmd->status = BFA_STATUS_OK;
out:
	return 0;
}
