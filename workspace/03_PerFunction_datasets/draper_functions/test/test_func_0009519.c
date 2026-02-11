print_csv_discrete(struct sdr_record_common_sensor    *sensor,
		   const struct sensor_reading *sr)
{
	if (!sr->s_reading_valid  || sr->s_reading_unavailable) {
		printf("%02Xh,ns,%d.%d,No Reading",
		       sensor->keys.sensor_num,
		       sensor->entity.id,
		       sensor->entity.instance);
		return;
	}

	if (sr->s_has_analog_value) {
		printf("%s,%s,", sr->s_a_str, sr->s_a_units);
	} else {
		printf("%02Xh,", sensor->keys.sensor_num);
	}
	printf("ok,%d.%d,",
	       sensor->entity.id,
	       sensor->entity.instance);
	ipmi_sdr_print_discrete_state_mini(NULL, ", ",
		sensor->sensor.type,
		sensor->event_type,
		sr->s_data2,
		sr->s_data3);
}
