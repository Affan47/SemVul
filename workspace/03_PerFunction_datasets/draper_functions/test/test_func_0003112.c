mic_init_irq(void)
{
	struct mic_driver *mdrv = g_drv;

	mdrv->irq_info.irq_usage_count = kzalloc((sizeof(u32) *
			mdrv->intr_info.num_intr),
			GFP_KERNEL);
	if (!mdrv->irq_info.irq_usage_count)
		return -ENOMEM;
	return 0;
}
