c2_set_qp_state(struct c2_qp *qp, int c2_state)
{
	int new_state = to_ib_state(c2_state);

	pr_debug("%s: qp[%p] state modify %s --> %s\n",
	       __func__,
		qp,
		to_ib_state_str(qp->state),
		to_ib_state_str(new_state));
	qp->state = new_state;
}
