action_camera_set_speed (GPParams *p, unsigned int speed)
{
	GPPortInfo	info;
	GPPortType	type;


	CR (gp_camera_get_port_info (p->camera, &info));
	gp_port_info_get_type (info, &type);
	if (type != GP_PORT_SERIAL) {
		if ((p->flags & FLAGS_QUIET) == 0) {
			fprintf (stderr, _("You can only specify speeds for "
					   "serial ports."));
			fputc ('\n', stderr);
		}
		return (GP_ERROR_BAD_PARAMETERS);
	}

	return gp_camera_set_port_speed (p->camera, speed);
}
