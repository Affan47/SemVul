max1363_update_scan_mode(struct iio_dev *indio_dev,
				    const unsigned long *scan_mask)
{
	struct max1363_state *st = iio_priv(indio_dev);


	st->current_mode = max1363_match_mode(scan_mask, st->chip_info);
	if (!st->current_mode)
		return -EINVAL;
	max1363_set_scan_mode(st);
	return 0;
}
