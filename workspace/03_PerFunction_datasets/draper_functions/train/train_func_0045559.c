ipmi_sensor_print_compact(struct ipmi_intf *intf,
			  struct sdr_record_compact_sensor *sensor)
{
	char id[17];
	char *unitstr = "discrete";
	int validread = 1;
	uint8_t val = 0;
	struct ipmi_rs *rsp;

	if (sensor == NULL)
		return -1;

	memset(id, 0, sizeof (id));
	memcpy(id, sensor->id_string, 16);


	rsp = ipmi_sdr_get_sensor_reading_ipmb(intf,
					       sensor->keys.sensor_num,
					       sensor->keys.owner_id,
					       sensor->keys.lun);
	if (rsp == NULL) {
		lprintf(LOG_ERR, "Error reading sensor %s (#%02x)",
			id, sensor->keys.sensor_num);
		return -1;
	} else if (rsp->ccode || (rsp->data[1] & READING_UNAVAILABLE)) {
		validread = 0;
	} else if (!(rsp->data[1] & SCANNING_DISABLED)) {
		validread = 0;
	} else {

		val = rsp->data[0];
	}

	if (csv_output) {

	} else {
		if (!verbose) {


			printf("%-16s ", id);

			if (validread) {
				printf("| 0x%-8x | %-10s | 0x%02x%02x",
				       val, unitstr,
				       rsp->data[2], rsp->data[3]);
			} else {
				printf("| %-10s | %-10s | %-6s",
				       "na", unitstr, "na");
			}

			printf("| %-10s| %-10s| %-10s| %-10s| %-10s| %-10s",
			       "na", "na", "na", "na", "na", "na");
			printf("\n");
		} else {
			printf("Sensor ID              : %s (0x%x)\n",
			       id, sensor->keys.sensor_num);
			printf(" Entity ID             : %d.%d\n",
			       sensor->entity.id, sensor->entity.instance);
			printf(" Sensor Type (Discrete): %s\n",
			       ipmi_sdr_get_sensor_type_desc(sensor->sensor.
							     type));

         if(validread)
         {
            ipmi_sdr_print_discrete_state("States Asserted",
						      						sensor->sensor.type,
												      sensor->event_type,
												      rsp->data[2],
												      rsp->data[3]);
            printf("\n");
         } else {
	   printf(" Unable to read sensor: Device Not Present\n\n");
	 }

		}
	}

	return (validread ? 0 : -1 );
}
