lpfc_issue_els_adisc(struct lpfc_vport *vport, struct lpfc_nodelist *ndlp,
		     uint8_t retry)
{
	struct Scsi_Host *shost = lpfc_shost_from_vport(vport);
	struct lpfc_hba  *phba = vport->phba;
	ADISC *ap;
	struct lpfc_iocbq *elsiocb;
	uint8_t *pcmd;
	uint16_t cmdsize;

	cmdsize = (sizeof(uint32_t) + sizeof(ADISC));
	elsiocb = lpfc_prep_els_iocb(vport, 1, cmdsize, retry, ndlp,
				     ndlp->nlp_DID, ELS_CMD_ADISC);
	if (!elsiocb)
		return 1;

	pcmd = (uint8_t *) (((struct lpfc_dmabuf *) elsiocb->context2)->virt);


	*((uint32_t *) (pcmd)) = ELS_CMD_ADISC;
	pcmd += sizeof(uint32_t);


	ap = (ADISC *) pcmd;
	ap->hardAL_PA = phba->fc_pref_ALPA;
	memcpy(&ap->portName, &vport->fc_portname, sizeof(struct lpfc_name));
	memcpy(&ap->nodeName, &vport->fc_nodename, sizeof(struct lpfc_name));
	ap->DID = be32_to_cpu(vport->fc_myDID);

	lpfc_debugfs_disc_trc(vport, LPFC_DISC_TRC_ELS_CMD,
		"Issue ADISC:     did:x%x",
		ndlp->nlp_DID, 0, 0);

	phba->fc_stat.elsXmitADISC++;
	elsiocb->iocb_cmpl = lpfc_cmpl_els_adisc;
	spin_lock_irq(shost->host_lock);
	ndlp->nlp_flag |= NLP_ADISC_SND;
	spin_unlock_irq(shost->host_lock);
	if (lpfc_sli_issue_iocb(phba, LPFC_ELS_RING, elsiocb, 0) ==
	    IOCB_ERROR) {
		spin_lock_irq(shost->host_lock);
		ndlp->nlp_flag &= ~NLP_ADISC_SND;
		spin_unlock_irq(shost->host_lock);
		lpfc_els_free_iocb(phba, elsiocb);
		return 1;
	}
	return 0;
}
