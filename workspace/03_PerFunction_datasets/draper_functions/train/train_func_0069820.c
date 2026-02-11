irmo_packet_readi16(IrmoPacket *packet, unsigned int *i)
{
	uint8_t *data;

        irmo_return_val_if_fail(packet != NULL, 0);

	if (packet->pos + 2 > packet->len) {
		return 0;
        }

	data = packet->data + packet->pos;

	if (i != NULL) {
                *i = ((unsigned int) data[0]) << 8;
		*i |= (unsigned int) data[1];
	}

	packet->pos += 2;

	return 1;
}
