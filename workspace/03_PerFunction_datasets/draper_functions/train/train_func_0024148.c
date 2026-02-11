connect_port(bool isoutput, int port, Element* e, int e_port)
{
    if (port_active(isoutput, port)) {
	_ports[isoutput][port].assign(this, e, e_port, isoutput);
	return 0;
    } else
	return -1;
}
