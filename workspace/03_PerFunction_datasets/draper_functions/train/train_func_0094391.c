u132_roothub_setportfeature(struct u132 *u132, u16 wValue,
	u16 wIndex)
{
	if (wIndex == 0 || wIndex > u132->num_ports) {
		return -EINVAL;
	} else {
		int port_index = wIndex - 1;
		struct u132_port *port = &u132->port[port_index];
		port->Status &= ~(1 << wValue);
		switch (wValue) {
		case USB_PORT_FEAT_SUSPEND:
			return u132_write_pcimem(u132,
			       roothub.portstatus[port_index], RH_PS_PSS);
		case USB_PORT_FEAT_POWER:
			return u132_write_pcimem(u132,
			       roothub.portstatus[port_index], RH_PS_PPS);
		case USB_PORT_FEAT_RESET:
			return u132_roothub_portreset(u132, port_index);
		default:
			return -EPIPE;
		}
	}
}
