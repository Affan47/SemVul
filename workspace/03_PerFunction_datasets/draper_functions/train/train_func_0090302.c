search_for_qr(Block *loop)
{
    Statement *stm = NULL;
    Quadruple *qr = NULL;

    if (loop->pre_head == NULL)
	return qr;
    for (stm = loop->pre_head->stm_head;
	 stm != NULL; stm = stm->next) {
	if (stm->ope == OPE_DO) {
	    for (qr = stm->qr_head; qr != NULL; qr = qr->next) {
		if (qr->ope == OPE_CFOR || qr->ope == OPE_DODW
		    || qr->ope == OPE_CFORDW ||  qr->ope == OPE_DO)
		    break;
	    }

	    break;
	}
    }
    return qr;
}
