csio_mgmtm_cleanup(struct csio_mgmtm *mgmtm)
{
	struct csio_hw *hw = mgmtm->hw;
	struct csio_ioreq *io_req;
	struct list_head *tmp;
	uint32_t count;

	count = 30;

	while ((!list_empty(&mgmtm->active_q)) && count--) {
		spin_unlock_irq(&hw->lock);
		msleep(2000);
		spin_lock_irq(&hw->lock);
	}


	list_for_each(tmp, &mgmtm->active_q) {
		io_req = (struct csio_ioreq *) tmp;
		tmp = csio_list_prev(tmp);
		list_del_init(&io_req->sm.sm_list);
		mgmtm->stats.n_active--;
		if (io_req->io_cbfn) {

			io_req->wr_status = -ETIMEDOUT;
			io_req->io_cbfn(mgmtm->hw, io_req);
		}
	}
}
