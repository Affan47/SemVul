__lpfc_findnode_did(struct lpfc_vport *vport, uint32_t did)
{
	struct lpfc_nodelist *ndlp;
	uint32_t data1;

	list_for_each_entry(ndlp, &vport->fc_nodes, nlp_listp) {
		if (lpfc_matchdid(vport, ndlp, did)) {
			data1 = (((uint32_t) ndlp->nlp_state << 24) |
				 ((uint32_t) ndlp->nlp_xri << 16) |
				 ((uint32_t) ndlp->nlp_type << 8) |
				 ((uint32_t) ndlp->nlp_rpi & 0xff));
			lpfc_printf_vlog(vport, KERN_INFO, LOG_NODE,
					 "0929 FIND node DID "
					 "Data: x%p x%x x%x x%x %p\n",
					 ndlp, ndlp->nlp_DID,
					 ndlp->nlp_flag, data1,
					 ndlp->active_rrqs_xri_bitmap);
			return ndlp;
		}
	}


	lpfc_printf_vlog(vport, KERN_INFO, LOG_NODE,
			 "0932 FIND node did x%x NOT FOUND.\n", did);
	return NULL;
}
