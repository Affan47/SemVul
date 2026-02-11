lpfc_nlp_remove(struct lpfc_vport *vport, struct lpfc_nodelist *ndlp)
{
	struct lpfc_hba  *phba = vport->phba;
	struct lpfc_rport_data *rdata;
	struct fc_rport *rport;
	LPFC_MBOXQ_t *mbox;
	int rc;

	lpfc_cancel_retry_delay_tmo(vport, ndlp);
	if ((ndlp->nlp_flag & NLP_DEFER_RM) &&
	    !(ndlp->nlp_flag & NLP_REG_LOGIN_SEND) &&
	    !(ndlp->nlp_flag & NLP_RPI_REGISTERED) &&
	    phba->sli_rev != LPFC_SLI_REV4) {


		lpfc_printf_vlog(vport, KERN_INFO, LOG_NODE,
				 "0005 rpi:%x DID:%x flg:%x %d map:%x %p\n",
				 ndlp->nlp_rpi, ndlp->nlp_DID, ndlp->nlp_flag,
				 atomic_read(&ndlp->kref.refcount),
				 ndlp->nlp_usg_map, ndlp);
		if ((mbox = mempool_alloc(phba->mbox_mem_pool, GFP_KERNEL))
			!= NULL) {
			rc = lpfc_reg_rpi(phba, vport->vpi, ndlp->nlp_DID,
			    (uint8_t *) &vport->fc_sparam, mbox, ndlp->nlp_rpi);
			if (rc) {
				mempool_free(mbox, phba->mbox_mem_pool);
			}
			else {
				mbox->mbox_flag |= LPFC_MBX_IMED_UNREG;
				mbox->mbox_cmpl = lpfc_mbx_cmpl_dflt_rpi;
				mbox->vport = vport;
				mbox->context2 = ndlp;
				rc =lpfc_sli_issue_mbox(phba, mbox, MBX_NOWAIT);
				if (rc == MBX_NOT_FINISHED) {
					mempool_free(mbox, phba->mbox_mem_pool);
				}
			}
		}
	}
	lpfc_cleanup_node(vport, ndlp);


	if (ndlp->rport) {


		lpfc_printf_vlog(vport, KERN_WARNING, LOG_NODE,
				"0940 removed node x%p DID x%x "
				" rport not null %p\n",
				ndlp, ndlp->nlp_DID, ndlp->rport);
		rport = ndlp->rport;
		rdata = rport->dd_data;
		rdata->pnode = NULL;
		ndlp->rport = NULL;
		put_device(&rport->dev);
	}
}
