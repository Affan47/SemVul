efx_ef10_filter_push_prep(struct efx_nic *efx,
				      const struct efx_filter_spec *spec,
				      efx_dword_t *inbuf, u64 handle,
				      bool replacing)
{
	struct efx_ef10_nic_data *nic_data = efx->nic_data;

	memset(inbuf, 0, MC_CMD_FILTER_OP_IN_LEN);

	if (replacing) {
		MCDI_SET_DWORD(inbuf, FILTER_OP_IN_OP,
			       MC_CMD_FILTER_OP_IN_OP_REPLACE);
		MCDI_SET_QWORD(inbuf, FILTER_OP_IN_HANDLE, handle);
	} else {
		u32 match_fields = 0;

		MCDI_SET_DWORD(inbuf, FILTER_OP_IN_OP,
			       efx_ef10_filter_is_exclusive(spec) ?
			       MC_CMD_FILTER_OP_IN_OP_INSERT :
			       MC_CMD_FILTER_OP_IN_OP_SUBSCRIBE);


		if (spec->match_flags & EFX_FILTER_MATCH_LOC_MAC_IG)
			match_fields |=
				is_multicast_ether_addr(spec->loc_mac) ?
				1 << MC_CMD_FILTER_OP_IN_MATCH_UNKNOWN_MCAST_DST_LBN :
				1 << MC_CMD_FILTER_OP_IN_MATCH_UNKNOWN_UCAST_DST_LBN;
#define COPY_FIELD(gen_flag, gen_field, mcdi_field)			     \
		if (spec->match_flags & EFX_FILTER_MATCH_ ## gen_flag) {     \
			match_fields |=					     \
				1 << MC_CMD_FILTER_OP_IN_MATCH_ ##	     \
				mcdi_field ## _LBN;			     \
			BUILD_BUG_ON(					     \
				MC_CMD_FILTER_OP_IN_ ## mcdi_field ## _LEN < \
				sizeof(spec->gen_field));		     \
			memcpy(MCDI_PTR(inbuf, FILTER_OP_IN_ ##	mcdi_field), \
			       &spec->gen_field, sizeof(spec->gen_field));   \
		}
		COPY_FIELD(REM_HOST, rem_host, SRC_IP);
		COPY_FIELD(LOC_HOST, loc_host, DST_IP);
		COPY_FIELD(REM_MAC, rem_mac, SRC_MAC);
		COPY_FIELD(REM_PORT, rem_port, SRC_PORT);
		COPY_FIELD(LOC_MAC, loc_mac, DST_MAC);
		COPY_FIELD(LOC_PORT, loc_port, DST_PORT);
		COPY_FIELD(ETHER_TYPE, ether_type, ETHER_TYPE);
		COPY_FIELD(INNER_VID, inner_vid, INNER_VLAN);
		COPY_FIELD(OUTER_VID, outer_vid, OUTER_VLAN);
		COPY_FIELD(IP_PROTO, ip_proto, IP_PROTO);
#undef COPY_FIELD
		MCDI_SET_DWORD(inbuf, FILTER_OP_IN_MATCH_FIELDS,
			       match_fields);
	}

	MCDI_SET_DWORD(inbuf, FILTER_OP_IN_PORT_ID, nic_data->vport_id);
	MCDI_SET_DWORD(inbuf, FILTER_OP_IN_RX_DEST,
		       spec->dmaq_id == EFX_FILTER_RX_DMAQ_ID_DROP ?
		       MC_CMD_FILTER_OP_IN_RX_DEST_DROP :
		       MC_CMD_FILTER_OP_IN_RX_DEST_HOST);
	MCDI_SET_DWORD(inbuf, FILTER_OP_IN_TX_DOMAIN, 0);
	MCDI_SET_DWORD(inbuf, FILTER_OP_IN_TX_DEST,
		       MC_CMD_FILTER_OP_IN_TX_DEST_DEFAULT);
	MCDI_SET_DWORD(inbuf, FILTER_OP_IN_RX_QUEUE,
		       spec->dmaq_id == EFX_FILTER_RX_DMAQ_ID_DROP ?
		       0 : spec->dmaq_id);
	MCDI_SET_DWORD(inbuf, FILTER_OP_IN_RX_MODE,
		       (spec->flags & EFX_FILTER_FLAG_RX_RSS) ?
		       MC_CMD_FILTER_OP_IN_RX_MODE_RSS :
		       MC_CMD_FILTER_OP_IN_RX_MODE_SIMPLE);
	if (spec->flags & EFX_FILTER_FLAG_RX_RSS)
		MCDI_SET_DWORD(inbuf, FILTER_OP_IN_RX_CONTEXT,
			       spec->rss_context !=
			       EFX_FILTER_RSS_CONTEXT_DEFAULT ?
			       spec->rss_context : nic_data->rx_rss_context);
}
