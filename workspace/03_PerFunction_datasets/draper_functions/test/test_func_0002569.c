is_ephemeral(int port)
{
	if (!ip_local_port_min) {
		FILE *f = ephemeral_ports_open();
		if (f) {
			fscanf(f, "%d %d",
			       &ip_local_port_min, &ip_local_port_max);
			fclose(f);
		} else {
			ip_local_port_min = 1024;
			ip_local_port_max = 4999;
		}
	}

	return (port >= ip_local_port_min && port<= ip_local_port_max);
}
