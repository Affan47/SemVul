lpfc_els_rcv_rpl(struct lpfc_vport *vport, struct lpfc_iocbq *cmdiocb,
		 struct lpfc_nodelist *ndlp)
{
	struct lpfc_dmabuf *pcmd;
	uint32_t *lp;
	uint32_t maxsize;
	uint16_t cmdsize;
	RPL *rpl;
	struct ls_rjt stat;

	if ((ndlp->nlp_state != NLP_STE_UNMAPPED_NODE) &&
	    (ndlp->nlp_state != NLP_STE_MAPPED_NODE)) {

		stat.un.b.lsRjtRsvd0 = 0;
		stat.un.b.lsRjtRsnCode = LSRJT_UNABLE_TPC;
		stat.un.b.lsRjtRsnCodeExp = LSEXP_CANT_GIVE_DATA;
		stat.un.b.vendorUnique = 0;
		lpfc_els_rsp_reject(vport, stat.un.lsRjtError, cmdiocb, ndlp,
			NULL);

		return 0;
	}

	pcmd = (struct lpfc_dmabuf *) cmdiocb->context2;
	lp = (uint32_t *) pcmd->virt;
	rpl = (RPL *) (lp + 1);
	maxsize = be32_to_cpu(rpl->maxsize);


	if ((rpl->index == 0) &&
	    ((maxsize == 0) ||
	     ((maxsize * sizeof(uint32_t)) >= sizeof(RPL_RSP)))) {
		cmdsize = sizeof(uint32_t) + sizeof(RPL_RSP);
	} else {
		cmdsize = sizeof(uint32_t) + maxsize * sizeof(uint32_t);
	}
	lpfc_els_rsp_rpl_acc(vport, cmdsize, cmdiocb, ndlp);

	return 0;
}
