generic_ide_remove(struct device *dev)
{
	ide_drive_t *drive = to_ide_device(dev);
	struct ide_driver *drv = to_ide_driver(dev->driver);

	if (drv->remove)
		drv->remove(drive);

	return 0;
}
