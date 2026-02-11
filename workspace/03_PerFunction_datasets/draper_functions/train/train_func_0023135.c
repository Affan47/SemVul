ipmi_get_power_consumption_data(struct ipmi_intf * intf,uint8_t unit)
{
	SensorReadingType sensorReadingData;

	struct ipmi_rs * rsp=NULL;
	struct sdr_record_list *sdr;
	int readingbtuphr = 0;
	int warning_threshbtuphr = 0;
	int failure_threshbtuphr = 0;
	int status = 0;
	int sensor_number = 0;
	sdr = ipmi_sdr_find_sdr_byid(intf, "System Level");
	if (sdr == NULL) {
		lprintf(LOG_ERR,
				"Error : Can not access the System Level sensor data");
		return -1;
	}
	sensor_number = sdr->record.common->keys.sensor_num;
	ipmi_get_sensor_reading(intf,sensor_number,&sensorReadingData);
	rsp = ipmi_sdr_get_sensor_thresholds(intf,
			sdr->record.common->keys.sensor_num,
			sdr->record.common->keys.owner_id,
			sdr->record.common->keys.lun,
			sdr->record.common->keys.channel);
	if (rsp == NULL || rsp->ccode != 0) {
		lprintf(LOG_ERR,
				"Error : Can not access the System Level sensor data");
		return -1;
	}
	readingbtuphr = sdr_convert_sensor_reading(sdr->record.full,
			sensorReadingData.sensorReading);
	warning_threshbtuphr = sdr_convert_sensor_reading(sdr->record.full,
			rsp->data[4]);
	failure_threshbtuphr = sdr_convert_sensor_reading(sdr->record.full,
			rsp->data[5]);

	printf("System Board System Level\n");
	if (unit == btuphr) {
		readingbtuphr = watt_to_btuphr_conversion(readingbtuphr);
		warning_threshbtuphr = watt_to_btuphr_conversion(warning_threshbtuphr);
		failure_threshbtuphr = watt_to_btuphr_conversion( failure_threshbtuphr);

		printf("Reading                        : %d BTU/hr\n", readingbtuphr);
		printf("Warning threshold      : %d BTU/hr\n", warning_threshbtuphr);
		printf("Failure threshold      : %d BTU/hr\n", failure_threshbtuphr);
	} else {
		printf("Reading                        : %d W \n",readingbtuphr);
		printf("Warning threshold      : %d W \n",(warning_threshbtuphr));
		printf("Failure threshold      : %d W \n",(failure_threshbtuphr));
	}
	return status;
}
