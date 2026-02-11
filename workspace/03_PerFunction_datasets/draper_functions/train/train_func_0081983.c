eeprom_93xx46_remove(struct spi_device *spi)
{
	struct eeprom_93xx46_dev *edev = spi_get_drvdata(spi);

	if (!(edev->pdata->flags & EE_READONLY))
		device_remove_file(&spi->dev, &dev_attr_erase);

	sysfs_remove_bin_file(&spi->dev.kobj, &edev->bin);
	kfree(edev);
	return 0;
}
