hfi1_get_credit(struct hfi1_qp *qp, u32 aeth)
{
	u32 credit = (aeth >> HFI1_AETH_CREDIT_SHIFT) & HFI1_AETH_CREDIT_MASK;


	if (credit == HFI1_AETH_CREDIT_INVAL) {
		if (!(qp->s_flags & HFI1_S_UNLIMITED_CREDIT)) {
			qp->s_flags |= HFI1_S_UNLIMITED_CREDIT;
			if (qp->s_flags & HFI1_S_WAIT_SSN_CREDIT) {
				qp->s_flags &= ~HFI1_S_WAIT_SSN_CREDIT;
				hfi1_schedule_send(qp);
			}
		}
	} else if (!(qp->s_flags & HFI1_S_UNLIMITED_CREDIT)) {

		credit = (aeth + credit_table[credit]) & HFI1_MSN_MASK;
		if (cmp_msn(credit, qp->s_lsn) > 0) {
			qp->s_lsn = credit;
			if (qp->s_flags & HFI1_S_WAIT_SSN_CREDIT) {
				qp->s_flags &= ~HFI1_S_WAIT_SSN_CREDIT;
				hfi1_schedule_send(qp);
			}
		}
	}
}
