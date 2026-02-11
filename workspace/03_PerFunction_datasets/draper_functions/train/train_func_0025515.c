lpfc_sli4_post_dev_loss_tmo_handler(struct lpfc_hba *phba, int fcf_inuse,
				    uint32_t nlp_did)
{


	if (!fcf_inuse)
		return;

	if ((phba->hba_flag & HBA_FIP_SUPPORT) && !lpfc_fcf_inuse(phba)) {
		spin_lock_irq(&phba->hbalock);
		if (phba->fcf.fcf_flag & FCF_DISCOVERY) {
			if (phba->hba_flag & HBA_DEVLOSS_TMO) {
				spin_unlock_irq(&phba->hbalock);
				return;
			}
			phba->hba_flag |= HBA_DEVLOSS_TMO;
			lpfc_printf_log(phba, KERN_INFO, LOG_FIP,
					"2847 Last remote node (x%x) using "
					"FCF devloss tmo\n", nlp_did);
		}
		if (phba->fcf.fcf_flag & FCF_REDISC_PROG) {
			spin_unlock_irq(&phba->hbalock);
			lpfc_printf_log(phba, KERN_INFO, LOG_FIP,
					"2868 Devloss tmo to FCF rediscovery "
					"in progress\n");
			return;
		}
		if (!(phba->hba_flag & (FCF_TS_INPROG | FCF_RR_INPROG))) {
			spin_unlock_irq(&phba->hbalock);
			lpfc_printf_log(phba, KERN_INFO, LOG_FIP,
					"2869 Devloss tmo to idle FIP engine, "
					"unreg in-use FCF and rescan.\n");

			lpfc_unregister_fcf_rescan(phba);
			return;
		}
		spin_unlock_irq(&phba->hbalock);
		if (phba->hba_flag & FCF_TS_INPROG)
			lpfc_printf_log(phba, KERN_INFO, LOG_FIP,
					"2870 FCF table scan in progress\n");
		if (phba->hba_flag & FCF_RR_INPROG)
			lpfc_printf_log(phba, KERN_INFO, LOG_FIP,
					"2871 FLOGI roundrobin FCF failover "
					"in progress\n");
	}
	lpfc_unregister_unused_fcf(phba);
}
