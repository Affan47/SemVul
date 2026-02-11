flow_spec_to_ntuple(struct ethtool_rx_flow_spec *fsp,
			       struct ethtool_rx_ntuple_flow_spec *ntuple)
{
	size_t i;


	if (fsp->location != RX_CLS_LOC_ANY)
		return -1;


	if (fsp->flow_type & FLOW_MAC_EXT)
		return -1;


	if (fsp->ring_cookie > INT_MAX && fsp->ring_cookie < (u64)(-2))
		return -1;


	if ((fsp->flow_type & FLOW_EXT) &&
	    (fsp->m_ext.data[0] || fsp->m_ext.data[1]) &&
	    fsp->m_ext.vlan_etype)
		return -1;


	memset(ntuple, ~0, sizeof(*ntuple));


	ntuple->flow_type = fsp->flow_type;
	ntuple->action = fsp->ring_cookie;


	memcpy(&ntuple->h_u, &fsp->h_u, sizeof(fsp->h_u));


	memcpy(&ntuple->m_u, &fsp->m_u, sizeof(fsp->m_u));
	for (i = 0; i < sizeof(fsp->m_u); i++)
		ntuple->m_u.hdata[i] ^= 0xFF;


	if (fsp->flow_type & FLOW_EXT) {
		ntuple->vlan_tag =
			ntohs(fsp->h_ext.vlan_tci);
		ntuple->vlan_tag_mask =
			~ntohs(fsp->m_ext.vlan_tci);
		if (fsp->m_ext.vlan_etype) {


			if (fsp->m_ext.data[0] || fsp->m_ext.data[1])
				return -1;
			ntuple->data =
				ntohl(fsp->h_ext.vlan_etype);
			ntuple->data_mask =
				~(u64)ntohl(fsp->m_ext.vlan_etype);
		} else {
			ntuple->data =
				(u64)ntohl(fsp->h_ext.data[0]) << 32;
			ntuple->data |=
				(u64)ntohl(fsp->h_ext.data[1]);
			ntuple->data_mask =
				(u64)ntohl(~fsp->m_ext.data[0]) << 32;
			ntuple->data_mask |=
				(u64)ntohl(~fsp->m_ext.data[1]);
		}
	}


	ntuple->flow_type &= ~FLOW_EXT;

	return 0;
}
