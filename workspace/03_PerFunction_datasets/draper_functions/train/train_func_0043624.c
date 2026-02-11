process_weapon_detonate_packet(ubyte *data, header *hinfo)
{
	ushort net_sig;
	int offset = HEADER_LENGTH;
	object *objp = NULL;


	GET_USHORT(net_sig);
	PACKET_SET_SIZE();


	objp = multi_get_network_object(net_sig);
	if((objp != NULL) && (objp->type == OBJ_WEAPON) && (objp->instance >= 0)){
		weapon_detonate(objp);
	}
}
