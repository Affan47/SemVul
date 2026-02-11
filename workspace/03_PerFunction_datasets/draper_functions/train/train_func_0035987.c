free_cntrs(struct hfi1_devdata *dd)
{
	struct hfi1_pportdata *ppd;
	int i;

	if (dd->synth_stats_timer.data)
		del_timer_sync(&dd->synth_stats_timer);
	dd->synth_stats_timer.data = 0;
	ppd = (struct hfi1_pportdata *)(dd + 1);
	for (i = 0; i < dd->num_pports; i++, ppd++) {
		kfree(ppd->cntrs);
		kfree(ppd->scntrs);
		free_percpu(ppd->ibport_data.rc_acks);
		free_percpu(ppd->ibport_data.rc_qacks);
		free_percpu(ppd->ibport_data.rc_delayed_comp);
		ppd->cntrs = NULL;
		ppd->scntrs = NULL;
		ppd->ibport_data.rc_acks = NULL;
		ppd->ibport_data.rc_qacks = NULL;
		ppd->ibport_data.rc_delayed_comp = NULL;
	}
	kfree(dd->portcntrnames);
	dd->portcntrnames = NULL;
	kfree(dd->cntrs);
	dd->cntrs = NULL;
	kfree(dd->scntrs);
	dd->scntrs = NULL;
	kfree(dd->cntrnames);
	dd->cntrnames = NULL;
}
