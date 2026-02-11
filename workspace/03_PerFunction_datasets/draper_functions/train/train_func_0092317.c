ad9523_reg_access(struct iio_dev *indio_dev,
			      unsigned reg, unsigned writeval,
			      unsigned *readval)
{
	int ret;

	mutex_lock(&indio_dev->mlock);
	if (readval == NULL) {
		ret = ad9523_write(indio_dev, reg | AD9523_R1B, writeval);
		ad9523_io_update(indio_dev);
	} else {
		ret = ad9523_read(indio_dev, reg | AD9523_R1B);
		if (ret < 0)
			goto out_unlock;
		*readval = ret;
		ret = 0;
	}

out_unlock:
	mutex_unlock(&indio_dev->mlock);

	return ret;
}
