isa_ide_controller_outb(void *_cpssp, unsigned char val, unsigned short port)
{
	struct cpssp *cpssp = (struct cpssp *) _cpssp;

	if (cpssp->port_0_7 < port && port < cpssp->port_0_7 + 8) {
		sig_ide_bus_outw(cpssp->sig_ide_bus,
				port - cpssp->port_0_7, val);
		return 0;
	} else if (cpssp->port_8 == port) {
		sig_ide_bus_outw(cpssp->sig_ide_bus,
				port - cpssp->port_8 + 8, val);
		return 0;
	}

	return -1;
}
