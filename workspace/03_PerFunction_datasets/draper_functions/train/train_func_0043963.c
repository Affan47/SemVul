lpfc_drain_txq(struct lpfc_hba *phba)
{
	LIST_HEAD(completions);
	struct lpfc_sli_ring *pring = &phba->sli.ring[LPFC_ELS_RING];
	struct lpfc_iocbq *piocbq = NULL;
	unsigned long iflags = 0;
	char *fail_msg = NULL;
	struct lpfc_sglq *sglq;
	union lpfc_wqe wqe;
	uint32_t txq_cnt = 0;

	spin_lock_irqsave(&pring->ring_lock, iflags);
	list_for_each_entry(piocbq, &pring->txq, list) {
		txq_cnt++;
	}

	if (txq_cnt > pring->txq_max)
		pring->txq_max = txq_cnt;

	spin_unlock_irqrestore(&pring->ring_lock, iflags);

	while (!list_empty(&pring->txq)) {
		spin_lock_irqsave(&pring->ring_lock, iflags);

		piocbq = lpfc_sli_ringtx_get(phba, pring);
		if (!piocbq) {
			spin_unlock_irqrestore(&pring->ring_lock, iflags);
			lpfc_printf_log(phba, KERN_ERR, LOG_SLI,
				"2823 txq empty and txq_cnt is %d\n ",
				txq_cnt);
			break;
		}
		sglq = __lpfc_sli_get_sglq(phba, piocbq);
		if (!sglq) {
			__lpfc_sli_ringtx_put(phba, pring, piocbq);
			spin_unlock_irqrestore(&pring->ring_lock, iflags);
			break;
		}
		txq_cnt--;


		piocbq->sli4_lxritag = sglq->sli4_lxritag;
		piocbq->sli4_xritag = sglq->sli4_xritag;
		if (NO_XRI == lpfc_sli4_bpl2sgl(phba, piocbq, sglq))
			fail_msg = "to convert bpl to sgl";
		else if (lpfc_sli4_iocb2wqe(phba, piocbq, &wqe))
			fail_msg = "to convert iocb to wqe";
		else if (lpfc_sli4_wq_put(phba->sli4_hba.els_wq, &wqe))
			fail_msg = " - Wq is full";
		else
			lpfc_sli_ringtxcmpl_put(phba, pring, piocbq);

		if (fail_msg) {

			lpfc_printf_log(phba, KERN_ERR, LOG_SLI,
					"2822 IOCB failed %s iotag 0x%x "
					"xri 0x%x\n",
					fail_msg,
					piocbq->iotag, piocbq->sli4_xritag);
			list_add_tail(&piocbq->list, &completions);
		}
		spin_unlock_irqrestore(&pring->ring_lock, iflags);
	}


	lpfc_sli_cancel_iocbs(phba, &completions, IOSTAT_LOCAL_REJECT,
				IOERR_SLI_ABORTED);

	return txq_cnt;
}
