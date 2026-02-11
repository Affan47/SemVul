device_close(struct gn_statemachine *state)
{
	dprintf("Serial device: closing device\n");

	switch (state->device.type) {
	case GN_CT_DKU2:
	case GN_CT_Serial:
	case GN_CT_Infrared:
		serial_close(state->device.fd, state);
		break;
	case GN_CT_Irda:
		irda_close(state->device.fd, state);
		break;
	case GN_CT_Bluetooth:
		bluetooth_close(state->device.fd, state);
		break;
	case GN_CT_Tekram:
		tekram_close(state->device.fd, state);
		break;
	case GN_CT_TCP:
		tcp_close(state->device.fd, state);
		break;
	case GN_CT_DKU2LIBUSB:
		fbusdku2usb_close(state);
		break;
	case GN_CT_SOCKETPHONET:
		socketphonet_close(state);
		break;
	default:
		break;
	}

	free(state->device.device_instance);
	state->device.device_instance = NULL;
}
