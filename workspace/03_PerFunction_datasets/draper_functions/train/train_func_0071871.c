smssdio_remove(struct sdio_func *func)
{
	struct smssdio_device *smsdev;

	smsdev = sdio_get_drvdata(func);


	if (smsdev->split_cb)
		smscore_putbuffer(smsdev->coredev, smsdev->split_cb);

	smscore_unregister_device(smsdev->coredev);

	sdio_claim_host(func);
	sdio_release_irq(func);
	sdio_disable_func(func);
	sdio_release_host(func);

	kfree(smsdev);
}
