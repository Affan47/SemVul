can_handle_new_request(RADIUS_PACKET *packet,
				  RADCLIENT *client,
				  struct main_config_t *root)
{


	if (root->max_requests) {
		int request_count = fr_packet_list_num_elements(pl);


		if (request_count > root->max_requests) {
			radlog(L_ERR, "Dropping request (%d is too many): "
			       "from client %s port %d - ID: %d", request_count,
			       client->shortname,
			       packet->src_port, packet->id);
			radlog(L_INFO, "WARNING: Please check the configuration file.\n"
			       "\tThe value for 'max_requests' is probably set too low.\n");
			return 0;
		}
	}


	return 1;
}
