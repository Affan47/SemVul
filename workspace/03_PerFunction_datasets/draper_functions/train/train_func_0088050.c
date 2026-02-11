focaltech_reconnect(struct psmouse *psmouse)
{
	int error;

	focaltech_reset(psmouse);

	error = focaltech_switch_protocol(psmouse);
	if (error) {
		psmouse_err(psmouse, "Unable to initialize the device\n");
		return error;
	}

	return 0;
}
