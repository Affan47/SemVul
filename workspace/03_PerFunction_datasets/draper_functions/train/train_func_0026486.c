sensors_chip_name_has_wildcards(const sensors_chip_name *chip)
{
	if ((chip->prefix == SENSORS_CHIP_NAME_PREFIX_ANY) ||
	    (chip->bus.type == SENSORS_BUS_TYPE_ANY) ||
	    (chip->bus.nr == SENSORS_BUS_NR_ANY) ||
	    (chip->addr == SENSORS_CHIP_NAME_ADDR_ANY))
		return 1;
	else
		return 0;
}
