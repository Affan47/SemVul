lpfc_sli4_fcf_rr_index_set(struct lpfc_hba *phba, uint16_t fcf_index)
{
	if (fcf_index >= LPFC_SLI4_FCF_TBL_INDX_MAX) {
		lpfc_printf_log(phba, KERN_ERR, LOG_FIP,
				"2610 FCF (x%x) reached driver's book "
				"keeping dimension:x%x\n",
				fcf_index, LPFC_SLI4_FCF_TBL_INDX_MAX);
		return -EINVAL;
	}

	set_bit(fcf_index, phba->fcf.fcf_rr_bmask);

	lpfc_printf_log(phba, KERN_INFO, LOG_FIP,
			"2790 Set FCF (x%x) to roundrobin FCF failover "
			"bmask\n", fcf_index);

	return 0;
}
