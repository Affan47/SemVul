is_serial_port_path(const char * port_name)
{
	if (!strncmp(port_name, SERIAL_PORT_PREFIX, strlen(SERIAL_PORT_PREFIX))) {
		return 1;
	}
	return 0;
}
