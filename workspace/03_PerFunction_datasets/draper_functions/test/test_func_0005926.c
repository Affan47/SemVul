print_sensor_min_max(struct sdr_record_full_sensor *full)
{
	if (!full) {
	    return;
	}

	double creading = 0.0;
	uint8_t is_analog = !UNITS_ARE_DISCRETE(&full->cmn);
	if (is_analog)
		creading = sdr_convert_sensor_reading(full, full->sensor_min);
	if ((full->cmn.unit.analog == 0 && full->sensor_min == 0x00) ||
	    (full->cmn.unit.analog == 1 && full->sensor_min == 0xff) ||
	    (full->cmn.unit.analog == 2 && full->sensor_min == 0x80) ||
	    (is_analog && (creading == 0.0)))
		printf(" Minimum sensor range  : Unspecified\n");
	else {
		if (is_analog)
			printf(" Minimum sensor range  : %.3f\n", creading);
		else
			printf(" Minimum sensor range  : 0x%02X\n", full->sensor_min);

	}
	if (is_analog)
		creading = sdr_convert_sensor_reading(full, full->sensor_max);
	if ((full->cmn.unit.analog == 0 && full->sensor_max == 0xff) ||
	    (full->cmn.unit.analog == 1 && full->sensor_max == 0x00) ||
	    (full->cmn.unit.analog == 2 && full->sensor_max == 0x7f) ||
	    (is_analog && (creading == 0.0)))
		printf(" Maximum sensor range  : Unspecified\n");
	else {
		if (is_analog)
			printf(" Maximum sensor range  : %.3f\n", creading);
		else
			printf(" Maximum sensor range  : 0x%02X\n", full->sensor_max);
	}
}
