be_cmd_set_vxlan_port(struct be_adapter *adapter, __be16 port)
{
	struct be_port_res_desc port_desc;

	memset(&port_desc, 0, sizeof(port_desc));
	port_desc.hdr.desc_type = PORT_RESOURCE_DESC_TYPE_V1;
	port_desc.hdr.desc_len = RESOURCE_DESC_SIZE_V1;
	port_desc.flags = (1 << IMM_SHIFT) | (1 << NOSV_SHIFT);
	port_desc.link_num = adapter->hba_port_num;
	if (port) {
		port_desc.nv_flags = NV_TYPE_VXLAN | (1 << SOCVID_SHIFT) |
					(1 << RCVID_SHIFT);
		port_desc.nv_port = swab16(port);
	} else {
		port_desc.nv_flags = NV_TYPE_DISABLED;
		port_desc.nv_port = 0;
	}

	return be_cmd_set_profile_config(adapter, &port_desc,
					 RESOURCE_DESC_SIZE_V1, 1, 1, 0);
}
