wacom_setup(struct wacom *wacom, struct serio *serio)
{
	int err;


	err = wacom_send_and_wait(wacom, serio, REQUEST_MODEL_AND_ROM_VERSION,
				  "model and version");
	if (err)
		return err;

	if (!(wacom->res_x && wacom->res_y)) {
		err = wacom_send_and_wait(wacom, serio,
					  REQUEST_CONFIGURATION_STRING,
					  "configuration string");
		if (err)
			return err;
	}

	if (!(wacom->max_x && wacom->max_y)) {
		err = wacom_send_and_wait(wacom, serio,
					  REQUEST_MAX_COORDINATES,
					  "coordinates string");
		if (err)
			return err;
	}

	return wacom_send_setup_string(wacom, serio);
}
