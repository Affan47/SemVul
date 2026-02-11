rocker_cmd_flow_tbl_add_vlan(struct rocker_desc_info *desc_info,
			     const struct rocker_flow_tbl_entry *entry)
{
	if (rocker_tlv_put_u32(desc_info, ROCKER_TLV_OF_DPA_IN_PPORT,
			       entry->key.vlan.in_pport))
		return -EMSGSIZE;
	if (rocker_tlv_put_be16(desc_info, ROCKER_TLV_OF_DPA_VLAN_ID,
				entry->key.vlan.vlan_id))
		return -EMSGSIZE;
	if (rocker_tlv_put_be16(desc_info, ROCKER_TLV_OF_DPA_VLAN_ID_MASK,
				entry->key.vlan.vlan_id_mask))
		return -EMSGSIZE;
	if (rocker_tlv_put_u16(desc_info, ROCKER_TLV_OF_DPA_GOTO_TABLE_ID,
			       entry->key.vlan.goto_tbl))
		return -EMSGSIZE;
	if (entry->key.vlan.untagged &&
	    rocker_tlv_put_be16(desc_info, ROCKER_TLV_OF_DPA_NEW_VLAN_ID,
				entry->key.vlan.new_vlan_id))
		return -EMSGSIZE;

	return 0;
}
