drv_CF_process_packet(void)
{

    switch (Packet.type) {

    case 0x02:


	switch (Packet.code) {

	case 0x00:

	    debug("Key Activity: %d", Packet.data[0]);
	    drv_generic_keypad_press(Packet.data[0]);
	    break;

	case 0x01:

	    if (Packet.data[1] == 0xff) {
		Fan_RPM[Packet.data[0]] = -1.0;
	    } else if (Packet.data[1] < 4) {
		Fan_RPM[Packet.data[0]] = 0.0;
	    } else {
		Fan_RPM[Packet.data[0]] =
		    (double) 27692308L *(Packet.data[1] - 3) / (Packet.data[2] + 256 * Packet.data[3]);
	    }
	    break;

	case 0x02:

	    switch (Packet.data[3]) {
	    case 0:
		error("%s: 1-Wire device #%d: CRC error", Name, Packet.data[0]);
		break;
	    case 1:
	    case 2:
		Temperature[Packet.data[0]] = (Packet.data[1] + 256 * Packet.data[2]) / 16.0;
		break;
	    default:
		error("%s: 1-Wire device #%d: unknown CRC status %d", Name, Packet.data[0], Packet.data[3]);
		break;
	    }
	    break;

	default:

	    error("%s: unexpected response type=0x%02x code=0x%02x size=%d", Name, Packet.type, Packet.code,
		  Packet.size);
	    break;
	}

	break;

    case 0x03:

	error("%s: error response type=0x%02x code=0x%02x size=%d", Name, Packet.type, Packet.code, Packet.size);
	break;

    default:


	error("%s: unexpected packet type=0x%02x code=0x%02x size=%d", Name, Packet.type, Packet.code, Packet.size);
	break;
    }

}
