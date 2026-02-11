process_emp_effect(ubyte *data, header *hinfo)
{
	float intensity, time;
	ushort net_sig;
	object *objp;
	int offset = HEADER_LENGTH;


	GET_USHORT(net_sig);
	GET_FLOAT(intensity);
	GET_FLOAT(time);
	PACKET_SET_SIZE();


	objp = multi_get_network_object(net_sig);
	if((objp != NULL) && (objp->type == OBJ_SHIP)){

		if(!(Net_player->flags & NETINFO_FLAG_OBSERVER) && (Player_obj != NULL) && (Player_obj->type == OBJ_SHIP) && (Player_obj == objp)){
			emp_start_local(intensity, time);
		}


		emp_start_ship(objp, intensity, time);
	}
}
