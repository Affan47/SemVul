cleanup_one_si(struct smi_info *to_clean)
{
	int           rv = 0;

	if (!to_clean)
		return;

	if (to_clean->intf) {
		ipmi_smi_t intf = to_clean->intf;

		to_clean->intf = NULL;
		rv = ipmi_unregister_smi(intf);
		if (rv) {
			pr_err(PFX "Unable to unregister device: errno=%d\n",
			       rv);
		}
	}

	if (to_clean->dev)
		dev_set_drvdata(to_clean->dev, NULL);

	list_del(&to_clean->link);


	if (to_clean->irq_cleanup)
		to_clean->irq_cleanup(to_clean);
	stop_timer_and_thread(to_clean);


	while (to_clean->curr_msg || (to_clean->si_state != SI_NORMAL)) {
		poll(to_clean);
		schedule_timeout_uninterruptible(1);
	}
	disable_si_irq(to_clean);
	while (to_clean->curr_msg || (to_clean->si_state != SI_NORMAL)) {
		poll(to_clean);
		schedule_timeout_uninterruptible(1);
	}

	if (to_clean->handlers)
		to_clean->handlers->cleanup(to_clean->si_sm);

	kfree(to_clean->si_sm);

	if (to_clean->addr_source_cleanup)
		to_clean->addr_source_cleanup(to_clean);
	if (to_clean->io_cleanup)
		to_clean->io_cleanup(to_clean);

	if (to_clean->dev_registered)
		platform_device_unregister(to_clean->pdev);

	kfree(to_clean);
}
