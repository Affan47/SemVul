ia_pd_nomatch_release(const struct data_string *client_id,
		      const struct data_string *iapref,
		      u_int32_t *ia_pd_id,
		      struct packet *packet,
		      char *reply_data,
		      int *reply_ofs,
		      int reply_len)
{
	char tmp_addr[INET6_ADDRSTRLEN];
	struct option_state *host_opt_state;
	int len;

	log_info("Client %s releases prefix %s/%u, which is not leased to it.",
		 print_hex_1(client_id->len, client_id->data, 60),
		 inet_ntop(AF_INET6, iapref->data + 9,
			   tmp_addr, sizeof(tmp_addr)),
		 (unsigned) getUChar(iapref->data + 8));


	host_opt_state = NULL;
	if (!option_state_allocate(&host_opt_state, MDL)) {
		log_error("ia_pd_nomatch_release: out of memory "
			  "allocating option_state.");
		goto exit;
	}

	if (!set_status_code(STATUS_NoBinding,
			     "Release for non-leased prefix.",
			     host_opt_state)) {
		goto exit;
	}


	if (reply_len < (*reply_ofs + 16)) {
		log_error("ia_pd_nomatch_release: "
			  "out of space for reply packet.");
		goto exit;
	}


	len = store_options6(reply_data+(*reply_ofs)+16,
			     reply_len-(*reply_ofs)-16,
			     host_opt_state, packet,
			     required_opts_STATUS_CODE, NULL);


	putUShort((unsigned char *)reply_data+(*reply_ofs), D6O_IA_PD);

	putUShort((unsigned char *)reply_data+(*reply_ofs)+2, len + 12);

	memcpy(reply_data+(*reply_ofs)+4, ia_pd_id, 4);

	putULong((unsigned char *)reply_data+(*reply_ofs)+8, 0);
	putULong((unsigned char *)reply_data+(*reply_ofs)+12, 0);


	*reply_ofs += (len + 16);

exit:
	option_state_dereference(&host_opt_state, MDL);
}
