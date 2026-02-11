i40e_get_udp_port_idx(struct i40e_pf *pf, __be16 port)
{
	u8 i;

	for (i = 0; i < I40E_MAX_PF_UDP_OFFLOAD_PORTS; i++) {
		if (pf->udp_ports[i].index == port)
			return i;
	}

	return i;
}
