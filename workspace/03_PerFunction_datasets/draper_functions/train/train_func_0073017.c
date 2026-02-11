ipmi_sdr_print_sensor_hysteresis(struct sdr_record_common_sensor *sensor,
		 struct sdr_record_full_sensor   *full,
		 uint8_t hysteresis_value,
		 const char *hvstr)
{


	if (!full || UNITS_ARE_DISCRETE(sensor)) {
		if ( hysteresis_value == 0x00 || hysteresis_value == 0xff ) {
			printf(" %s   : Unspecified\n", hvstr);
		} else {
			printf(" %s   : 0x%02X\n", hvstr, hysteresis_value);
		}
		return;
	}

	double creading = sdr_convert_sensor_hysterisis(full, hysteresis_value);
	if ( hysteresis_value == 0x00 || hysteresis_value == 0xff ||
	     creading == 0.0 ) {
		printf(" %s   : Unspecified\n", hvstr);
	} else {
		printf(" %s   : %.3f\n", hvstr, creading);
	}
}
