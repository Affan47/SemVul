ipmi_sdr_get_thresh_status(struct sensor_reading *sr, const char *invalidstr)
{
	uint8_t stat;
	if (!sr->s_reading_valid) {
	    return invalidstr;
	}
	stat = sr->s_data2;
	if (stat & SDR_SENSOR_STAT_LO_NR) {
		if (verbose)
			return "Lower Non-Recoverable";
		else if (sdr_extended)
			return "lnr";
		else
			return "nr";
	} else if (stat & SDR_SENSOR_STAT_HI_NR) {
		if (verbose)
			return "Upper Non-Recoverable";
		else if (sdr_extended)
			return "unr";
		else
			return "nr";
	} else if (stat & SDR_SENSOR_STAT_LO_CR) {
		if (verbose)
			return "Lower Critical";
		else if (sdr_extended)
			return "lcr";
		else
			return "cr";
	} else if (stat & SDR_SENSOR_STAT_HI_CR) {
		if (verbose)
			return "Upper Critical";
		else if (sdr_extended)
			return "ucr";
		else
			return "cr";
	} else if (stat & SDR_SENSOR_STAT_LO_NC) {
		if (verbose)
			return "Lower Non-Critical";
		else if (sdr_extended)
			return "lnc";
		else
			return "nc";
	} else if (stat & SDR_SENSOR_STAT_HI_NC) {
		if (verbose)
			return "Upper Non-Critical";
		else if (sdr_extended)
			return "unc";
		else
			return "nc";
	}
	return "ok";
}
