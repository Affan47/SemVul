ipmi_sdr_print_type(struct ipmi_intf *intf, char *type)
{
	struct sdr_record_list *list, *entry;
	int rc = 0;
	int x;
	uint8_t sensor_type = 0;

	if (type == NULL ||
	    strncasecmp(type, "help", 4) == 0 ||
	    strncasecmp(type, "list", 4) == 0) {
		printf("Sensor Types:\n");
		for (x = 1; x < SENSOR_TYPE_MAX; x += 2) {
			printf("\t%-25s (0x%02x)   %-25s (0x%02x)\n",
				sensor_type_desc[x], x,
				sensor_type_desc[x + 1], x + 1);
		}
		return 0;
	}

	if (strncmp(type, "0x", 2) == 0) {

		if (str2uchar(type, &sensor_type) != 0) {
			lprintf(LOG_ERR,
					"Given type of sensor \"%s\" is either invalid or out of range.",
					type);
			return (-1);
		}
	} else {
		for (x = 1; x < SENSOR_TYPE_MAX; x++) {
			if (strncasecmp(sensor_type_desc[x], type,
					__maxlen(type,
						 sensor_type_desc[x])) == 0) {
				sensor_type = x;
				break;
			}
		}
		if (sensor_type != x) {
			lprintf(LOG_ERR, "Sensor Type \"%s\" not found.",
				type);
			printf("Sensor Types:\n");
			for (x = 1; x < SENSOR_TYPE_MAX; x += 2) {
				printf("\t%-25s (0x%02x)   %-25s (0x%02x)\n",
					sensor_type_desc[x], x,
					sensor_type_desc[x + 1], x + 1);
			}
			return 0;
		}
	}

	list = ipmi_sdr_find_sdr_bysensortype(intf, sensor_type);

	for (entry = list; entry != NULL; entry = entry->next) {
		rc = ipmi_sdr_print_listentry(intf, entry);
	}

	__sdr_list_empty(list);

	return rc;
}
