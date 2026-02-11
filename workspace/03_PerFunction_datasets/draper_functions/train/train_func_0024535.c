append_set_param_qr(Statement *spt, Operand **op)
{
    Quadruple *qrpt;

    if(spt->qr_head != NULL){
	qrpt = search_last_qr(spt->qr_head);
	qrpt->next = construct_qr(OPE_DTU_SET_PARAM, op, 3, spt);
	qrpt->next->stm = spt;
	qrpt->next->prev = qrpt;
    }else{
	spt->qr_head = construct_qr(OPE_DTU_SET_PARAM, op, 3, spt);
	spt->qr_head->stm = spt;
    }
}
