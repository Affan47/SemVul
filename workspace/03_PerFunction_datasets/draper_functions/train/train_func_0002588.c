qib_create_workqueues(struct qib_devdata *dd)
{
	int pidx;
	struct qib_pportdata *ppd;

	for (pidx = 0; pidx < dd->num_pports; ++pidx) {
		ppd = dd->pport + pidx;
		if (!ppd->qib_wq) {
			char wq_name[8];

			snprintf(wq_name, sizeof(wq_name), "qib%d_%d",
				dd->unit, pidx);
			ppd->qib_wq =
				create_singlethread_workqueue(wq_name);
			if (!ppd->qib_wq)
				goto wq_error;
		}
	}
	return 0;
wq_error:
	pr_err("create_singlethread_workqueue failed for port %d\n",
		pidx + 1);
	for (pidx = 0; pidx < dd->num_pports; ++pidx) {
		ppd = dd->pport + pidx;
		if (ppd->qib_wq) {
			destroy_workqueue(ppd->qib_wq);
			ppd->qib_wq = NULL;
		}
	}
	return -ENOMEM;
}
