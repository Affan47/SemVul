ptp_clock_register(struct ptp_clock_info *info,
				     struct device *parent)
{
	struct ptp_clock *ptp;
	int err = 0, index, major = MAJOR(ptp_devt);

	if (info->n_alarm > PTP_MAX_ALARMS)
		return ERR_PTR(-EINVAL);


	err = -ENOMEM;
	ptp = kzalloc(sizeof(struct ptp_clock), GFP_KERNEL);
	if (ptp == NULL)
		goto no_memory;

	index = ida_simple_get(&ptp_clocks_map, 0, MINORMASK + 1, GFP_KERNEL);
	if (index < 0) {
		err = index;
		goto no_slot;
	}

	ptp->clock.ops = ptp_clock_ops;
	ptp->clock.release = delete_ptp_clock;
	ptp->info = info;
	ptp->devid = MKDEV(major, index);
	ptp->index = index;
	spin_lock_init(&ptp->tsevq.lock);
	mutex_init(&ptp->tsevq_mux);
	mutex_init(&ptp->pincfg_mux);
	init_waitqueue_head(&ptp->tsev_wq);


	ptp->dev = device_create(ptp_class, parent, ptp->devid, ptp,
				 "ptp%d", ptp->index);
	if (IS_ERR(ptp->dev))
		goto no_device;

	dev_set_drvdata(ptp->dev, ptp);

	err = ptp_populate_sysfs(ptp);
	if (err)
		goto no_sysfs;


	if (info->pps) {
		struct pps_source_info pps;
		memset(&pps, 0, sizeof(pps));
		snprintf(pps.name, PPS_MAX_NAME_LEN, "ptp%d", index);
		pps.mode = PTP_PPS_MODE;
		pps.owner = info->owner;
		ptp->pps_source = pps_register_source(&pps, PTP_PPS_DEFAULTS);
		if (!ptp->pps_source) {
			pr_err("failed to register pps source\n");
			goto no_pps;
		}
	}


	err = posix_clock_register(&ptp->clock, ptp->devid);
	if (err) {
		pr_err("failed to create posix clock\n");
		goto no_clock;
	}

	return ptp;

no_clock:
	if (ptp->pps_source)
		pps_unregister_source(ptp->pps_source);
no_pps:
	ptp_cleanup_sysfs(ptp);
no_sysfs:
	device_destroy(ptp_class, ptp->devid);
no_device:
	mutex_destroy(&ptp->tsevq_mux);
	mutex_destroy(&ptp->pincfg_mux);
no_slot:
	kfree(ptp);
no_memory:
	return ERR_PTR(err);
}
