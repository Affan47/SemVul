bfa_msgq_rspq_pi_update(struct bfa_msgq_rspq *rspq, struct bfi_mbmsg *mb)
{
	struct bfi_msgq_i2h_db *dbell = (struct bfi_msgq_i2h_db *)mb;
	struct bfi_msgq_mhdr *msghdr;
	int num_entries;
	int mc;
	u8 *rspq_qe;

	rspq->producer_index = ntohs(dbell->idx.rspq_pi);

	while (rspq->consumer_index != rspq->producer_index) {
		rspq_qe = (u8 *)rspq->addr.kva;
		rspq_qe += (rspq->consumer_index * BFI_MSGQ_RSP_ENTRY_SIZE);
		msghdr = (struct bfi_msgq_mhdr *)rspq_qe;

		mc = msghdr->msg_class;
		num_entries = ntohs(msghdr->num_entries);

		if ((mc >= BFI_MC_MAX) || (rspq->rsphdlr[mc].cbfn == NULL))
			break;

		(rspq->rsphdlr[mc].cbfn)(rspq->rsphdlr[mc].cbarg, msghdr);

		BFA_MSGQ_INDX_ADD(rspq->consumer_index, num_entries,
				rspq->depth);
	}

	bfa_fsm_send_event(rspq, RSPQ_E_RESP);
}
