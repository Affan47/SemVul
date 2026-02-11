ipr_reset_restore_cfg_space(struct ipr_cmnd *ipr_cmd)
{
	struct ipr_ioa_cfg *ioa_cfg = ipr_cmd->ioa_cfg;
	u32 int_reg;

	ENTER;
	ioa_cfg->pdev->state_saved = true;
	pci_restore_state(ioa_cfg->pdev);

	if (ipr_set_pcix_cmd_reg(ioa_cfg)) {
		ipr_cmd->s.ioasa.hdr.ioasc = cpu_to_be32(IPR_IOASC_PCI_ACCESS_ERROR);
		return IPR_RC_JOB_CONTINUE;
	}

	ipr_fail_all_ops(ioa_cfg);

	if (ioa_cfg->sis64) {

		writel(IPR_ENDIAN_SWAP_KEY, ioa_cfg->regs.endian_swap_reg);
		int_reg = readl(ioa_cfg->regs.endian_swap_reg);
	}

	if (ioa_cfg->ioa_unit_checked) {
		if (ioa_cfg->sis64) {
			ipr_cmd->job_step = ipr_reset_get_unit_check_job;
			ipr_reset_start_timer(ipr_cmd, IPR_DUMP_DELAY_TIMEOUT);
			return IPR_RC_JOB_RETURN;
		} else {
			ioa_cfg->ioa_unit_checked = 0;
			ipr_get_unit_check_buffer(ioa_cfg);
			ipr_cmd->job_step = ipr_reset_alert;
			ipr_reset_start_timer(ipr_cmd, 0);
			return IPR_RC_JOB_RETURN;
		}
	}

	if (ioa_cfg->in_ioa_bringdown) {
		ipr_cmd->job_step = ipr_ioa_bringdown_done;
	} else if (ioa_cfg->sdt_state == GET_DUMP) {
		ipr_cmd->job_step = ipr_dump_mailbox_wait;
		ipr_cmd->u.time_left = IPR_WAIT_FOR_MAILBOX;
	} else {
		ipr_cmd->job_step = ipr_reset_enable_ioa;
	}

	LEAVE;
	return IPR_RC_JOB_CONTINUE;
}
