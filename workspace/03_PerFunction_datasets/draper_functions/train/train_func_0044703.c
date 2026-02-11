pmbus_reg2data_vid(struct pmbus_data *data,
			       struct pmbus_sensor *sensor)
{
	long val = sensor->data;
	long rv = 0;

	switch (data->info->vrm_version) {
	case vr11:
		if (val >= 0x02 && val <= 0xb2)
			rv = DIV_ROUND_CLOSEST(160000 - (val - 2) * 625, 100);
		break;
	case vr12:
		if (val >= 0x01)
			rv = 250 + (val - 1) * 5;
		break;
	}
	return rv;
}
