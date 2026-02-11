lpfc_cmpl_els_flogi_nport(struct lpfc_vport *vport, struct lpfc_nodelist *ndlp,
			  struct serv_parm *sp)
{
	struct Scsi_Host *shost = lpfc_shost_from_vport(vport);
	struct lpfc_hba  *phba = vport->phba;
	LPFC_MBOXQ_t *mbox;
	int rc;

	spin_lock_irq(shost->host_lock);
	vport->fc_flag &= ~(FC_FABRIC | FC_PUBLIC_LOOP);
	vport->fc_flag |= FC_PT2PT;
	spin_unlock_irq(shost->host_lock);


	if ((phba->sli_rev == LPFC_SLI_REV4) && phba->fc_topology_changed) {
		lpfc_unregister_fcf_prep(phba);

		spin_lock_irq(shost->host_lock);
		vport->fc_flag &= ~FC_VFI_REGISTERED;
		spin_unlock_irq(shost->host_lock);
		phba->fc_topology_changed = 0;
	}

	rc = memcmp(&vport->fc_portname, &sp->portName,
		    sizeof(vport->fc_portname));

	if (rc >= 0) {

		spin_lock_irq(shost->host_lock);
		vport->fc_flag |= FC_PT2PT_PLOGI;
		spin_unlock_irq(shost->host_lock);


		if (rc)
			vport->fc_myDID = PT2PT_LocalID;


		lpfc_nlp_put(ndlp);

		ndlp = lpfc_findnode_did(vport, PT2PT_RemoteID);
		if (!ndlp) {


			ndlp = mempool_alloc(phba->nlp_mem_pool, GFP_KERNEL);
			if (!ndlp)
				goto fail;
			lpfc_nlp_init(vport, ndlp, PT2PT_RemoteID);
		} else if (!NLP_CHK_NODE_ACT(ndlp)) {
			ndlp = lpfc_enable_node(vport, ndlp,
						NLP_STE_UNUSED_NODE);
			if(!ndlp)
				goto fail;
		}

		memcpy(&ndlp->nlp_portname, &sp->portName,
		       sizeof(struct lpfc_name));
		memcpy(&ndlp->nlp_nodename, &sp->nodeName,
		       sizeof(struct lpfc_name));

		lpfc_nlp_set_state(vport, ndlp, NLP_STE_NPR_NODE);
		spin_lock_irq(shost->host_lock);
		ndlp->nlp_flag |= NLP_NPR_2B_DISC;
		spin_unlock_irq(shost->host_lock);
	} else


		lpfc_nlp_put(ndlp);


	phba->sli3_options &= ~LPFC_SLI3_NPIV_ENABLED;

	mbox = mempool_alloc(phba->mbox_mem_pool, GFP_KERNEL);
	if (!mbox)
		goto fail;

	lpfc_config_link(phba, mbox);

	mbox->mbox_cmpl = lpfc_mbx_cmpl_local_config_link;
	mbox->vport = vport;
	rc = lpfc_sli_issue_mbox(phba, mbox, MBX_NOWAIT);
	if (rc == MBX_NOT_FINISHED) {
		mempool_free(mbox, phba->mbox_mem_pool);
		goto fail;
	}

	return 0;
fail:
	return -ENXIO;
}
