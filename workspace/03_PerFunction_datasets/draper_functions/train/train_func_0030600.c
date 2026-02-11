hpi_tuner_get_status(u32 h_control, u16 *pw_status_mask, u16 *pw_status)
{
	u32 status = 0;
	u16 error = 0;

	error = hpi_control_param1_get(h_control, HPI_TUNER_STATUS, &status);
	if (pw_status) {
		if (!error) {
			*pw_status_mask = (u16)(status >> 16);
			*pw_status = (u16)(status & 0xFFFF);
		} else {
			*pw_status_mask = 0;
			*pw_status = 0;
		}
	}
	return error;
}
