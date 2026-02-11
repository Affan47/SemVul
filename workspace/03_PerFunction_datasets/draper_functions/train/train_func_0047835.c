rc_timeout(unsigned long arg)
{
	struct qib_qp *qp = (struct qib_qp *)arg;
	struct qib_ibport *ibp;
	unsigned long flags;

	spin_lock_irqsave(&qp->r_lock, flags);
	spin_lock(&qp->s_lock);
	if (qp->s_flags & QIB_S_TIMER) {
		ibp = to_iport(qp->ibqp.device, qp->port_num);
		ibp->n_rc_timeouts++;
		qp->s_flags &= ~QIB_S_TIMER;
		del_timer(&qp->s_timer);
		qib_restart_rc(qp, qp->s_last_psn + 1, 1);
		qib_schedule_send(qp);
	}
	spin_unlock(&qp->s_lock);
	spin_unlock_irqrestore(&qp->r_lock, flags);
}
