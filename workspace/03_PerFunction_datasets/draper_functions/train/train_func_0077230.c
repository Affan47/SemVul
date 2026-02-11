lpfc_sli_driver_resource_setup(struct lpfc_hba *phba)
{
	struct lpfc_sli *psli;
	int rc;


	init_timer(&phba->hb_tmofunc);
	phba->hb_tmofunc.function = lpfc_hb_timeout;
	phba->hb_tmofunc.data = (unsigned long)phba;

	psli = &phba->sli;

	init_timer(&psli->mbox_tmo);
	psli->mbox_tmo.function = lpfc_mbox_timeout;
	psli->mbox_tmo.data = (unsigned long) phba;

	init_timer(&phba->fcp_poll_timer);
	phba->fcp_poll_timer.function = lpfc_poll_timeout;
	phba->fcp_poll_timer.data = (unsigned long) phba;

	init_timer(&phba->fabric_block_timer);
	phba->fabric_block_timer.function = lpfc_fabric_block_timeout;
	phba->fabric_block_timer.data = (unsigned long) phba;

	init_timer(&phba->eratt_poll);
	phba->eratt_poll.function = lpfc_poll_eratt;
	phba->eratt_poll.data = (unsigned long) phba;


	phba->work_ha_mask = (HA_ERATT | HA_MBATT | HA_LATT);
	phba->work_ha_mask |= (HA_RXMASK << (LPFC_ELS_RING * 4));


	lpfc_get_cfgparam(phba);
	if (phba->pcidev->device == PCI_DEVICE_ID_HORNET) {
		phba->menlo_flag |= HBA_MENLO_SUPPORT;

		if (phba->cfg_sg_seg_cnt < LPFC_DEFAULT_MENLO_SG_SEG_CNT)
			phba->cfg_sg_seg_cnt = LPFC_DEFAULT_MENLO_SG_SEG_CNT;
	}

	if (!phba->sli.ring)
		phba->sli.ring = kzalloc(LPFC_SLI3_MAX_RING *
			sizeof(struct lpfc_sli_ring), GFP_KERNEL);
	if (!phba->sli.ring)
		return -ENOMEM;


	lpfc_vport_template.sg_tablesize = phba->cfg_sg_seg_cnt;
	lpfc_template_s3.sg_tablesize = phba->cfg_sg_seg_cnt;


	if (phba->cfg_enable_bg) {


		phba->cfg_sg_dma_buf_size = sizeof(struct fcp_cmnd) +
			sizeof(struct fcp_rsp) +
			(LPFC_MAX_SG_SEG_CNT * sizeof(struct ulp_bde64));

		if (phba->cfg_sg_seg_cnt > LPFC_MAX_SG_SEG_CNT_DIF)
			phba->cfg_sg_seg_cnt = LPFC_MAX_SG_SEG_CNT_DIF;


		phba->cfg_total_seg_cnt = LPFC_MAX_SG_SEG_CNT;
	} else {


		phba->cfg_sg_dma_buf_size = sizeof(struct fcp_cmnd) +
			sizeof(struct fcp_rsp) +
			((phba->cfg_sg_seg_cnt + 2) * sizeof(struct ulp_bde64));


		phba->cfg_total_seg_cnt = phba->cfg_sg_seg_cnt + 2;
	}

	lpfc_printf_log(phba, KERN_INFO, LOG_INIT | LOG_FCP,
			"9088 sg_tablesize:%d dmabuf_size:%d total_bde:%d\n",
			phba->cfg_sg_seg_cnt, phba->cfg_sg_dma_buf_size,
			phba->cfg_total_seg_cnt);

	phba->max_vpi = LPFC_MAX_VPI;

	phba->max_vports = 0;


	lpfc_sli_setup(phba);
	lpfc_sli_queue_setup(phba);


	if (lpfc_mem_alloc(phba, BPL_ALIGN_SZ))
		return -ENOMEM;


	if (phba->cfg_sriov_nr_virtfn > 0) {
		rc = lpfc_sli_probe_sriov_nr_virtfn(phba,
						 phba->cfg_sriov_nr_virtfn);
		if (rc) {
			lpfc_printf_log(phba, KERN_WARNING, LOG_INIT,
					"2808 Requested number of SR-IOV "
					"virtual functions (%d) is not "
					"supported\n",
					phba->cfg_sriov_nr_virtfn);
			phba->cfg_sriov_nr_virtfn = 0;
		}
	}

	return 0;
}
