hfi1_do_send(struct work_struct *work)
{
	struct iowait *wait = container_of(work, struct iowait, iowork);
	struct hfi1_qp *qp = container_of(wait, struct hfi1_qp, s_iowait);
	struct hfi1_ibport *ibp = to_iport(qp->ibqp.device, qp->port_num);
	struct hfi1_pportdata *ppd = ppd_from_ibp(ibp);
	int (*make_req)(struct hfi1_qp *qp);
	unsigned long flags;
	unsigned long timeout;

	if ((qp->ibqp.qp_type == IB_QPT_RC ||
	     qp->ibqp.qp_type == IB_QPT_UC) &&
	    !loopback &&
	    (qp->remote_ah_attr.dlid & ~((1 << ppd->lmc) - 1)) == ppd->lid) {
		ruc_loopback(qp);
		return;
	}

	if (qp->ibqp.qp_type == IB_QPT_RC)
		make_req = hfi1_make_rc_req;
	else if (qp->ibqp.qp_type == IB_QPT_UC)
		make_req = hfi1_make_uc_req;
	else
		make_req = hfi1_make_ud_req;

	spin_lock_irqsave(&qp->s_lock, flags);


	if (!hfi1_send_ok(qp)) {
		spin_unlock_irqrestore(&qp->s_lock, flags);
		return;
	}

	qp->s_flags |= HFI1_S_BUSY;

	spin_unlock_irqrestore(&qp->s_lock, flags);

	timeout = jiffies + SEND_RESCHED_TIMEOUT;
	do {

		if (qp->s_hdrwords != 0) {


			if (hfi1_verbs_send(qp, qp->s_hdr, qp->s_hdrwords,
					    qp->s_cur_sge, qp->s_cur_size))
				break;

			qp->s_hdrwords = 0;
		}


		if (unlikely(time_after(jiffies, timeout))) {
			cond_resched();
			ppd->dd->verbs_dev.n_send_schedule++;
			timeout = jiffies + SEND_RESCHED_TIMEOUT;
		}
	} while (make_req(qp));
}
