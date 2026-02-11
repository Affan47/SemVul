zd_chip_clear(struct zd_chip *chip)
{
	ZD_ASSERT(!mutex_is_locked(&chip->mutex));
	zd_usb_clear(&chip->usb);
	zd_rf_clear(&chip->rf);
	mutex_destroy(&chip->mutex);
	ZD_MEMCLEAR(chip, sizeof(*chip));
}
