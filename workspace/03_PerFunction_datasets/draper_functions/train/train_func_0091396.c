fm10k_tlv_attr_get_mac_vlan(u32 *attr, u8 *mac_addr, u16 *vlan)
{

	if (!mac_addr || !attr)
		return FM10K_ERR_PARAM;

	*(__le32 *)&mac_addr[0] = cpu_to_le32(attr[1]);
	*(__le16 *)&mac_addr[4] = cpu_to_le16((u16)(attr[2]));
	*vlan = (u16)(attr[2] >> 16);

	return 0;
}
