isert_cq_work(struct work_struct *work)
{
	enum { isert_poll_budget = 65536 };
	struct isert_comp *comp = container_of(work, struct isert_comp,
					       work);
	struct ib_wc *const wcs = comp->wcs;
	int i, n, completed = 0;

	while ((n = ib_poll_cq(comp->cq, ARRAY_SIZE(comp->wcs), wcs)) > 0) {
		for (i = 0; i < n; i++)
			isert_handle_wc(&wcs[i]);

		completed += n;
		if (completed >= isert_poll_budget)
			break;
	}

	ib_req_notify_cq(comp->cq, IB_CQ_NEXT_COMP);
}
