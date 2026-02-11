send_wing_create_packet( wing *wingp, int num_to_create, int pre_create_count )
{
	int packet_size, index, ship_instance;
	ubyte data[MAX_PACKET_SIZE];
	ushort signature;
	int val;


	index = WING_INDEX(wingp);
	ship_instance = wingp->ship_index[wingp->current_count - num_to_create];
	signature = Objects[Ships[ship_instance].objnum].net_signature;

	BUILD_HEADER( WING_CREATE );
	ADD_INT(index);
	ADD_INT(num_to_create);
	ADD_USHORT(signature);
	ADD_INT(pre_create_count);
	val = wingp->current_wave - 1;
	ADD_INT(val);

	multi_io_send_to_all_reliable(data, packet_size);
}
