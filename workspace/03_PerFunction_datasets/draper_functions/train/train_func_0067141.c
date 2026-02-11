dhcp_failover_send_bind_update (dhcp_failover_state_t *state,
					     struct lease *lease)
{
	dhcp_failover_link_t *link;
	isc_result_t status;
	int flags = 0;
	binding_state_t transmit_state;
#if defined (DEBUG_FAILOVER_MESSAGES)
	char obuf [64];
	unsigned obufix = 0;

# define FMA obuf, &obufix, sizeof obuf
	failover_print (FMA, "(bndupd");
#else
# define FMA (char *)0, (unsigned *)0, 0
#endif

	if (!state -> link_to_peer ||
	    state -> link_to_peer -> type != dhcp_type_failover_link)
		return DHCP_R_INVALIDARG;
	link = (dhcp_failover_link_t *)state -> link_to_peer;

	if (!link -> outer || link -> outer -> type != omapi_type_connection)
		return DHCP_R_INVALIDARG;

	transmit_state = lease->desired_binding_state;
	if (lease->flags & RESERVED_LEASE) {


		if ((state->i_am == primary) && (transmit_state == FTS_FREE))
			transmit_state = FTS_BACKUP;
		else if ((state->i_am == secondary) &&
			 (transmit_state == FTS_BACKUP))
			transmit_state = FTS_FREE;

		flags |= FTF_IP_FLAG_RESERVE;
	}
	if (lease->flags & BOOTP_LEASE)
		flags |= FTF_IP_FLAG_BOOTP;


	if (link->xid == 0)
		link->xid = 1;

	lease->last_xid = link->xid++;


	if (lease->rewind_binding_state != lease->binding_state) {
		lease->rewind_binding_state = lease->binding_state;

		write_lease(lease);
		commit_leases();
	}


	status = (dhcp_failover_put_message
		  (link, link -> outer,
		   FTM_BNDUPD, lease->last_xid,
		   dhcp_failover_make_option (FTO_ASSIGNED_IP_ADDRESS, FMA,
					      lease -> ip_addr.len,
					      lease -> ip_addr.iabuf),
		   dhcp_failover_make_option (FTO_BINDING_STATUS, FMA,
					      lease -> desired_binding_state),
		   lease -> uid_len
		   ? dhcp_failover_make_option (FTO_CLIENT_IDENTIFIER, FMA,
						lease -> uid_len,
						lease -> uid)
		   : &skip_failover_option,
		   lease -> hardware_addr.hlen
		   ? dhcp_failover_make_option (FTO_CHADDR, FMA,
						lease -> hardware_addr.hlen,
						lease -> hardware_addr.hbuf)
		   : &skip_failover_option,
		   dhcp_failover_make_option (FTO_LEASE_EXPIRY, FMA,
					      lease -> ends),
		   dhcp_failover_make_option (FTO_POTENTIAL_EXPIRY, FMA,
					      lease -> tstp),
		   dhcp_failover_make_option (FTO_STOS, FMA,
					      lease -> starts),
		   (lease->cltt != 0) ?
			dhcp_failover_make_option(FTO_CLTT, FMA, lease->cltt) :
			&skip_failover_option,
		   flags ? dhcp_failover_make_option(FTO_IP_FLAGS, FMA,
						     flags) :
			   &skip_failover_option,
		   &skip_failover_option,
		   &skip_failover_option,
		   &skip_failover_option,
		   (failover_option_t *)0));

#if defined (DEBUG_FAILOVER_MESSAGES)
	if (status != ISC_R_SUCCESS)
		failover_print (FMA, " (failed)");
	failover_print (FMA, ")");
	if (obufix) {
		log_debug ("%s", obuf);
	}
#endif
	return status;
}
