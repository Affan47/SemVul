lpfc_cancel_all_vport_retry_delay_timer(struct lpfc_hba *phba)
{
	struct lpfc_vport **vports;
	struct lpfc_nodelist *ndlp;
	uint32_t link_state;
	int i;


	link_state = phba->link_state;
	lpfc_linkdown(phba);
	phba->link_state = link_state;

	vports = lpfc_create_vport_work_array(phba);

	if (vports) {
		for (i = 0; i <= phba->max_vports && vports[i] != NULL; i++) {
			ndlp = lpfc_findnode_did(vports[i], Fabric_DID);
			if (ndlp)
				lpfc_cancel_retry_delay_tmo(vports[i], ndlp);
			lpfc_els_flush_cmd(vports[i]);
		}
		lpfc_destroy_vport_work_array(phba, vports);
	}
}
