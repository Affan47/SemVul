tpm_add_char_device(struct tpm_chip *chip)
{
	int rc;

	rc = cdev_add(&chip->cdev, chip->dev.devt, 1);
	if (rc) {
		dev_err(&chip->dev,
			"unable to cdev_add() %s, major %d, minor %d, err=%d\n",
			chip->devname, MAJOR(chip->dev.devt),
			MINOR(chip->dev.devt), rc);

		return rc;
	}

	rc = device_add(&chip->dev);
	if (rc) {
		dev_err(&chip->dev,
			"unable to device_register() %s, major %d, minor %d, err=%d\n",
			chip->devname, MAJOR(chip->dev.devt),
			MINOR(chip->dev.devt), rc);

		cdev_del(&chip->cdev);
		return rc;
	}


	mutex_lock(&idr_lock);
	idr_replace(&dev_nums_idr, chip, chip->dev_num);
	mutex_unlock(&idr_lock);

	return rc;
}
