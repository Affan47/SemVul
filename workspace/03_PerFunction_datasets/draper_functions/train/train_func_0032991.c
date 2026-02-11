ignore_bogus_interrupt(ctlr_info_t *h)
{
	if (likely(!reset_devices))
		return 0;

	if (likely(h->interrupts_enabled))
		return 0;

	dev_info(&h->pdev->dev, "Received interrupt while interrupts disabled "
		"(known firmware bug.)  Ignoring.\n");

	return 1;
}
