idChip(const sensors_chip_name *chip)
{
	const char *name, *adapter;

	name = chipName(chip);
	if (!name) {
		sensorLog(LOG_ERR, "Error getting chip name");
		return -1;
	}

	sensorLog(LOG_INFO, "Chip: %s", name);

	adapter = sensors_get_adapter_name(&chip->bus);
	if (!adapter)
		sensorLog(LOG_INFO, "Error getting adapter name");
	else
		sensorLog(LOG_INFO, "Adapter: %s", adapter);

	return 0;
}
