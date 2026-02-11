turn_create_permission(int verbose, app_ur_conn_info *clnet_info,
		ioa_addr *peer_addr, int addrnum)
{

	if(no_permissions || (addrnum<1))
		return 0;

	char saddr[129]="\0";
	if (verbose) {
		addr_to_string(peer_addr,(u08bits*)saddr);
	}

	stun_buffer request_message, response_message;

	beg_cp:

	{
		int cp_sent = 0;

		stun_init_request(STUN_METHOD_CREATE_PERMISSION, &request_message);
		{
			int addrindex;
			for(addrindex=0;addrindex<addrnum;++addrindex) {
				stun_attr_add_addr(&request_message, STUN_ATTRIBUTE_XOR_PEER_ADDRESS, peer_addr+addrindex);
			}
		}

		add_origin(&request_message);

		if(add_integrity(clnet_info, &request_message)<0) return -1;

		stun_attr_add_fingerprint_str(request_message.buf,(size_t*)&(request_message.len));

		while (!cp_sent) {

			int len = send_buffer(clnet_info, &request_message, 0,0);

			if (len > 0) {
				if (verbose) {
					TURN_LOG_FUNC(TURN_LOG_LEVEL_INFO, "create perm sent: %s\n",saddr);
				}
				cp_sent = 1;
			} else {
				perror("send");
				exit(1);
			}
		}
	}


	if(not_rare_event()) return 0;


	{
		int cp_received = 0;
		while (!cp_received) {

			int len = recv_buffer(clnet_info, &response_message, 1, 0, NULL, &request_message);
			if (len > 0) {
				if (verbose) {
					TURN_LOG_FUNC(TURN_LOG_LEVEL_INFO,
							"cp response received: \n");
				}
				int err_code = 0;
				u08bits err_msg[129];
				if (stun_is_success_response(&response_message)) {

					cp_received = 1;

					if(clnet_info->nonce[0] || use_short_term) {
						if(check_integrity(clnet_info, &response_message)<0)
							return -1;
					}

					if (verbose) {
						TURN_LOG_FUNC(TURN_LOG_LEVEL_INFO, "success\n");
					}
				} else if (stun_is_challenge_response_str(response_message.buf, (size_t)response_message.len,
									&err_code,err_msg,sizeof(err_msg),
									clnet_info->realm,clnet_info->nonce,
									clnet_info->server_name, &(clnet_info->oauth))) {
					if(err_code == SHA_TOO_WEAK_ERROR_CODE && (clnet_info->shatype == SHATYPE_SHA1)) {
						clnet_info->shatype = SHATYPE_SHA256;
						recalculate_restapi_hmac();
					}
					goto beg_cp;
				} else if (stun_is_error_response(&response_message, &err_code,err_msg,sizeof(err_msg))) {
					cp_received = 1;
					TURN_LOG_FUNC(TURN_LOG_LEVEL_INFO, "create permission error %d (%s)\n",
							      err_code,(char*)err_msg);
					return -1;
				} else {
					TURN_LOG_FUNC(TURN_LOG_LEVEL_INFO, "unknown create permission response\n");

				}
			} else {
				perror("recv");
				exit(-1);
			}
		}
	}

	return 0;
}
