process_wing_create_packet( ubyte *data, header *hinfo )
{
	int offset, index, num_to_create;
	ushort signature;
	int total_arrived_count, current_wave;

	offset = HEADER_LENGTH;
	GET_INT(index);
	GET_INT(num_to_create);
	GET_USHORT(signature);
	GET_INT(total_arrived_count);
	GET_INT(current_wave);

	PACKET_SET_SIZE();


	if ( (index < 0) || (index >= Num_wings) || (Wings[index].num_waves == -1) ) {
		nprintf(("Network", "invalid index %d for wing create packet\n"));
		return;
	}
	if ( (num_to_create <= 0) || (num_to_create > Wings[index].wave_count) ) {
		nprintf(("Network", "Invalid number of ships to create (%d) for wing %s\n", num_to_create, Wings[index].name));
		return;
	}


	Wings[index].current_count = 0;
	Wings[index].total_arrived_count = total_arrived_count;
	Wings[index].current_wave = current_wave;


	multi_set_network_signature( signature, MULTI_SIG_SHIP );
	parse_wing_create_ships( &Wings[index], num_to_create, 1 );
}
