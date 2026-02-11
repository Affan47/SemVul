libshut_get_report(int upsfd, int ReportId,
		       unsigned char *raw_buf, int ReportSize )
{
	if (upsfd < 1) {
		return 0;
	}

	upsdebugx(4, "Entering libshut_get_report");

	return shut_control_msg(upsfd,
		REQUEST_TYPE_GET_REPORT,

		 0x01,
		 ReportId+(0x03<<8),
		 0, raw_buf, ReportSize, SHUT_TIMEOUT);
}
