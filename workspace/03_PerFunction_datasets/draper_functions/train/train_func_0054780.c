cypress_set_absolute_mode(struct psmouse *psmouse)
{
	struct cytp_data *cytp = psmouse->private;
	unsigned char param[3];

	if (cypress_send_ext_cmd(psmouse, CYTP_CMD_ABS_WITH_PRESSURE_MODE, param) < 0)
		return -1;

	cytp->mode = (cytp->mode & ~CYTP_BIT_ABS_REL_MASK)
			| CYTP_BIT_ABS_PRESSURE;
	cypress_set_packet_size(psmouse, 5);

	return 0;
}
