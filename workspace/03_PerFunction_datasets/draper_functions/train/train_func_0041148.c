nes_cm_disconn(struct nes_qp *nesqp)
{
	struct disconn_work *work;

	work = kzalloc(sizeof *work, GFP_ATOMIC);
	if (!work)
		return -ENOMEM;

	nes_add_ref(&nesqp->ibqp);
	work->nesqp = nesqp;
	INIT_WORK(&work->work, nes_disconnect_worker);
	queue_work(g_cm_core->disconn_wq, &work->work);
	return 0;
}
