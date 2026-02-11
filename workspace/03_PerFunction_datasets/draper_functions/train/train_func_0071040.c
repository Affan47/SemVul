setChip(const sensors_chip_name *chip)
{
	int ret = 0;
	if ((ret = idChip(chip))) {
		sensorLog(LOG_ERR, "Error identifying chip: %s",
			  chip->prefix);
	} else if ((ret = sensors_do_chip_sets(chip))) {
		sensorLog(LOG_ERR, "Error performing chip sets: %s: %s",
			  chip->prefix, sensors_strerror(ret));
		ret = 50;
	} else {
		sensorLog(LOG_INFO, "Set.");
	}
	return ret;
}
