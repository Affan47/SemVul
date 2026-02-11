send_weapon_or_ammo_changed_packet (int ship_index, int bank_type, int bank_number, int ammo_left, int rearm_limit, int new_weapon_index)
{
	ubyte data[MAX_PACKET_SIZE];
	int packet_size = 0;

	if(Net_player == NULL){
		return;
	}
	if(!(Net_player->flags & NETINFO_FLAG_AM_MASTER)){
		return;
	}


	BUILD_HEADER(WEAPON_OR_AMMO_CHANGED);
	ADD_INT(ship_index);
	ADD_INT(bank_type);
	ADD_INT(bank_number);
	ADD_INT(ammo_left);
	ADD_INT(rearm_limit);
	ADD_INT(new_weapon_index);


	multi_io_send_to_all_reliable(data, packet_size);
}
