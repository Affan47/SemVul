lpfc_cmpl_ct(struct lpfc_hba *phba, struct lpfc_iocbq *cmdiocb,
	     struct lpfc_iocbq *rspiocb)
{
	struct lpfc_vport *vport = cmdiocb->vport;
	struct lpfc_dmabuf *inp;
	struct lpfc_dmabuf *outp;
	IOCB_t *irsp;
	struct lpfc_sli_ct_request *CTrsp;
	struct lpfc_nodelist *ndlp;
	int cmdcode, rc;
	uint8_t retry;
	uint32_t latt;


	ndlp = cmdiocb->context_un.ndlp;


	cmdiocb->context_un.rsp_iocb = rspiocb;

	inp = (struct lpfc_dmabuf *) cmdiocb->context1;
	outp = (struct lpfc_dmabuf *) cmdiocb->context2;
	irsp = &rspiocb->iocb;

	cmdcode = be16_to_cpu(((struct lpfc_sli_ct_request *) inp->virt)->
					CommandResponse.bits.CmdRsp);
	CTrsp = (struct lpfc_sli_ct_request *) outp->virt;

	latt = lpfc_els_chk_latt(vport);


	lpfc_printf_vlog(vport, KERN_INFO, LOG_DISCOVERY,
			 "0209 CT Request completes, latt %d, "
			 "ulpStatus x%x CmdRsp x%x, Context x%x, Tag x%x\n",
			 latt, irsp->ulpStatus,
			 CTrsp->CommandResponse.bits.CmdRsp,
			 cmdiocb->iocb.ulpContext, cmdiocb->iocb.ulpIoTag);

	lpfc_debugfs_disc_trc(vport, LPFC_DISC_TRC_CT,
		"CT cmd cmpl:     status:x%x/x%x cmd:x%x",
		irsp->ulpStatus, irsp->un.ulpWord[4], cmdcode);

	if (irsp->ulpStatus) {
		lpfc_printf_vlog(vport, KERN_ERR, LOG_DISCOVERY,
				 "0268 NS cmd x%x Error (x%x x%x)\n",
				 cmdcode, irsp->ulpStatus, irsp->un.ulpWord[4]);

		if ((irsp->ulpStatus == IOSTAT_LOCAL_REJECT) &&
			(((irsp->un.ulpWord[4] & IOERR_PARAM_MASK) ==
			  IOERR_SLI_DOWN) ||
			 ((irsp->un.ulpWord[4] & IOERR_PARAM_MASK) ==
			  IOERR_SLI_ABORTED)))
			goto out;

		retry = cmdiocb->retry;
		if (retry >= LPFC_MAX_NS_RETRY)
			goto out;

		retry++;
		lpfc_printf_vlog(vport, KERN_INFO, LOG_DISCOVERY,
				 "0250 Retrying NS cmd %x\n", cmdcode);
		rc = lpfc_ns_cmd(vport, cmdcode, retry, 0);
		if (rc == 0)
			goto out;
	}

out:
	cmdiocb->context_un.ndlp = ndlp;
	lpfc_ct_free_iocb(phba, cmdiocb);
	return;
}
