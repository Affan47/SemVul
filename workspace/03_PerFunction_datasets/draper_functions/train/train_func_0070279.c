irmo_proto_verify_packet(IrmoPacket *packet, IrmoClient *client,
                             unsigned int flags)
{
	int result = 1;
	unsigned int origpos;

        origpos = irmo_packet_get_position(packet);


	if (flags & PACKET_FLAG_ACK) {
		unsigned int ack;

		if (!irmo_packet_readi16(packet, &ack)) {
			result = 0;
                }
	}

	if (result && (flags & PACKET_FLAG_DTA) != 0) {
		if (!proto_verify_packet_cluster(packet, client)) {
			result = 0;
                }
	}


        irmo_packet_set_position(packet, origpos);

	return result;
}
