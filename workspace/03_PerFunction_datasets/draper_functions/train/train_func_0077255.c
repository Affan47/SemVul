savu_report_to_chrdev(struct roccat_common2_device const *savu,
		u8 const *data)
{
	struct savu_roccat_report roccat_report;
	struct savu_mouse_report_special const *special_report;

	if (data[0] != SAVU_MOUSE_REPORT_NUMBER_SPECIAL)
		return;

	special_report = (struct savu_mouse_report_special const *)data;

	roccat_report.type = special_report->type;
	roccat_report.data[0] = special_report->data[0];
	roccat_report.data[1] = special_report->data[1];
	roccat_report_event(savu->chrdev_minor,
			(uint8_t const *)&roccat_report);
}
