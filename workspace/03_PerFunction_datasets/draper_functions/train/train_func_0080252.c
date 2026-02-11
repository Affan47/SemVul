fb3110_rx_state_machine(unsigned char rx_byte, struct gn_statemachine *state)
{
	fb3110_incoming_frame *i = &FBUSINST(state)->i;

	if (!i)
		return;

	switch (i->state) {


	case FB3110_RX_Discarding:
		if (rx_byte != 0x55)
			break;


		i->state = FB3110_RX_Sync;

		dprintf("restarting.\n");


	case FB3110_RX_Sync:
		if (rx_byte == 0x04 || rx_byte == 0x03) {
			i->frame_type = rx_byte;
			i->checksum = rx_byte;
			i->state = FB3110_RX_GetLength;
		}
		break;


	case FB3110_RX_GetLength:
		i->frame_len = rx_byte;
		i->buffer_count = 0;
		i->checksum ^= rx_byte;
		i->state = FB3110_RX_GetMessage;
		break;


	case FB3110_RX_GetMessage:
		i->buffer[i->buffer_count] = rx_byte;
		i->buffer_count++;

		if (i->buffer_count >= FB3110_FRAME_MAX_LENGTH) {
			dprintf("FBUS: Message buffer overun - resetting\n");
			i->state = FB3110_RX_Sync;
			break;
		}


		if (i->buffer_count > i->frame_len) {


			if (rx_byte == i->checksum) {

				fb3110_rx_frame_handle(i, state);
			} else {

				dprintf("Bad checksum!\n");
			}
			i->state = FB3110_RX_Sync;
		}
		i->checksum ^= rx_byte;
		break;
	}
}
