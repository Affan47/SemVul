r852_unregister_nand_device(struct r852_device *dev)
{
	if (!dev->card_registred)
		return;

	device_remove_file(&dev->mtd->dev, &dev_attr_media_type);
	nand_release(dev->mtd);
	r852_engine_disable(dev);
	dev->card_registred = 0;
	kfree(dev->mtd);
	dev->mtd = NULL;
}
