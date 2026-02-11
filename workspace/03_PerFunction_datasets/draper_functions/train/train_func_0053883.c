pps_register_source(struct pps_source_info *info,
		int default_params)
{
	struct pps_device *pps;
	int err;


	if ((info->mode & default_params) != default_params) {
		pr_err("%s: unsupported default parameters\n",
					info->name);
		err = -EINVAL;
		goto pps_register_source_exit;
	}
	if ((info->mode & (PPS_TSFMT_TSPEC | PPS_TSFMT_NTPFP)) == 0) {
		pr_err("%s: unspecified time format\n",
					info->name);
		err = -EINVAL;
		goto pps_register_source_exit;
	}


	pps = kzalloc(sizeof(struct pps_device), GFP_KERNEL);
	if (pps == NULL) {
		err = -ENOMEM;
		goto pps_register_source_exit;
	}


	pps->params.api_version = PPS_API_VERS;
	pps->params.mode = default_params;
	pps->info = *info;


	if ((pps->info.mode & (PPS_ECHOASSERT | PPS_ECHOCLEAR)) &&
			pps->info.echo == NULL)
		pps->info.echo = pps_echo_client_default;

	init_waitqueue_head(&pps->queue);
	spin_lock_init(&pps->lock);


	err = pps_register_cdev(pps);
	if (err < 0) {
		pr_err("%s: unable to create char device\n",
					info->name);
		goto kfree_pps;
	}

	dev_info(pps->dev, "new PPS source %s\n", info->name);

	return pps;

kfree_pps:
	kfree(pps);

pps_register_source_exit:
	pr_err("%s: unable to register source\n", info->name);

	return NULL;
}
