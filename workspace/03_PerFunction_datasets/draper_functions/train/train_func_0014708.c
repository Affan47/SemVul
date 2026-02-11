device_changespeed(int speed, struct gn_statemachine *state)
{
	switch (state->device.type) {
	case GN_CT_DKU2:
	case GN_CT_Serial:
	case GN_CT_Infrared:
		dprintf("Serial device: setting speed to %d\n", speed);
		serial_changespeed(state->device.fd, speed, state);
		break;
	case GN_CT_Tekram:
		dprintf("Serial device: setting speed to %d\n", speed);
		tekram_changespeed(state->device.fd, speed, state);
		break;
	case GN_CT_Irda:
	case GN_CT_Bluetooth:
	case GN_CT_TCP:
	case GN_CT_DKU2LIBUSB:
	case GN_CT_SOCKETPHONET:
	default:
		break;
	}
}
