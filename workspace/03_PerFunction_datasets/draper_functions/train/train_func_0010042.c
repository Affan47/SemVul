wacom_handle_configuration_response(struct wacom *wacom)
{
	int r, skip;

	dev_dbg(&wacom->dev->dev, "Configuration string: %s\n", wacom->data);
	r = sscanf(wacom->data, "~R%x,%u,%u,%u,%u", &skip, &skip, &skip,
		   &wacom->res_x, &wacom->res_y);
	if (r != 5)
		dev_warn(&wacom->dev->dev, "could not get resolution\n");
}
