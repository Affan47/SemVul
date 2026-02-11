solo_ring_start(struct solo_dev *solo_dev)
{
	solo_dev->ring_thread = kthread_run(solo_ring_thread, solo_dev,
					    SOLO6X10_NAME "_ring");
	if (IS_ERR(solo_dev->ring_thread)) {
		int err = PTR_ERR(solo_dev->ring_thread);

		solo_dev->ring_thread = NULL;
		return err;
	}

	solo_irq_on(solo_dev, SOLO_IRQ_ENCODER);

	return 0;
}
