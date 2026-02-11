device_setdtrrts(int dtr, int rts, struct gn_statemachine *state)
{
	switch (state->device.type) {
	case GN_CT_DKU2:
	case GN_CT_Serial:
	case GN_CT_Infrared:
		dprintf("Serial device: setting RTS to %s and DTR to %s\n", rts ? "high" : "low", dtr ? "high" : "low");
		serial_setdtrrts(state->device.fd, dtr, rts, state);
		break;
	case GN_CT_Irda:
	case GN_CT_Bluetooth:
	case GN_CT_Tekram:
	case GN_CT_TCP:
	case GN_CT_DKU2LIBUSB:
	case GN_CT_SOCKETPHONET:
	default:
		break;
	}
}
