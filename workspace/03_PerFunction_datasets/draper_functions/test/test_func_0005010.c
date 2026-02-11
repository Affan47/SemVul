ipr_reset_enable_ioa(struct ipr_cmnd *ipr_cmd)
{
	struct ipr_ioa_cfg *ioa_cfg = ipr_cmd->ioa_cfg;
	volatile u32 int_reg;
	volatile u64 maskval;
	int i;

	ENTER;
	ipr_cmd->job_step = ipr_ioafp_identify_hrrq;
	ipr_init_ioa_mem(ioa_cfg);

	for (i = 0; i < ioa_cfg->hrrq_num; i++) {
		spin_lock(&ioa_cfg->hrrq[i]._lock);
		ioa_cfg->hrrq[i].allow_interrupts = 1;
		spin_unlock(&ioa_cfg->hrrq[i]._lock);
	}
	wmb();
	if (ioa_cfg->sis64) {

		writel(IPR_ENDIAN_SWAP_KEY, ioa_cfg->regs.endian_swap_reg);
		int_reg = readl(ioa_cfg->regs.endian_swap_reg);
	}

	int_reg = readl(ioa_cfg->regs.sense_interrupt_reg32);

	if (int_reg & IPR_PCII_IOA_TRANS_TO_OPER) {
		writel((IPR_PCII_ERROR_INTERRUPTS | IPR_PCII_HRRQ_UPDATED),
		       ioa_cfg->regs.clr_interrupt_mask_reg32);
		int_reg = readl(ioa_cfg->regs.sense_interrupt_mask_reg);
		return IPR_RC_JOB_CONTINUE;
	}


	writel(ioa_cfg->doorbell, ioa_cfg->regs.set_uproc_interrupt_reg32);

	if (ioa_cfg->sis64) {
		maskval = IPR_PCII_IPL_STAGE_CHANGE;
		maskval = (maskval << 32) | IPR_PCII_OPER_INTERRUPTS;
		writeq(maskval, ioa_cfg->regs.clr_interrupt_mask_reg);
	} else
		writel(IPR_PCII_OPER_INTERRUPTS, ioa_cfg->regs.clr_interrupt_mask_reg32);

	int_reg = readl(ioa_cfg->regs.sense_interrupt_mask_reg);

	dev_info(&ioa_cfg->pdev->dev, "Initializing IOA.\n");

	if (ioa_cfg->sis64) {
		ipr_cmd->job_step = ipr_reset_next_stage;
		return IPR_RC_JOB_CONTINUE;
	}

	ipr_cmd->timer.data = (unsigned long) ipr_cmd;
	ipr_cmd->timer.expires = jiffies + (ioa_cfg->transop_timeout * HZ);
	ipr_cmd->timer.function = (void (*)(unsigned long))ipr_oper_timeout;
	ipr_cmd->done = ipr_reset_ioa_job;
	add_timer(&ipr_cmd->timer);
	list_add_tail(&ipr_cmd->queue, &ipr_cmd->hrrq->hrrq_pending_q);

	LEAVE;
	return IPR_RC_JOB_RETURN;
}
