adis16400_debugfs_init(struct iio_dev *indio_dev)
{
	struct adis16400_state *st = iio_priv(indio_dev);

	if (st->variant->flags & ADIS16400_HAS_SERIAL_NUMBER)
		debugfs_create_file("serial_number", 0400,
			indio_dev->debugfs_dentry, st,
			&adis16400_serial_number_fops);
	if (st->variant->flags & ADIS16400_HAS_PROD_ID)
		debugfs_create_file("product_id", 0400,
			indio_dev->debugfs_dentry, st,
			&adis16400_product_id_fops);
	debugfs_create_file("flash_count", 0400, indio_dev->debugfs_dentry,
		st, &adis16400_flash_count_fops);

	return 0;
}
