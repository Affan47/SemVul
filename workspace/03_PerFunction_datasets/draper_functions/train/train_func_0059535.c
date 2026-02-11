rocker_cmd_group_tbl_add_l2_rewrite(struct rocker_desc_info *desc_info,
				    const struct rocker_group_tbl_entry *entry)
{
	if (rocker_tlv_put_u32(desc_info, ROCKER_TLV_OF_DPA_GROUP_ID_LOWER,
			       entry->l2_rewrite.group_id))
		return -EMSGSIZE;
	if (!is_zero_ether_addr(entry->l2_rewrite.eth_src) &&
	    rocker_tlv_put(desc_info, ROCKER_TLV_OF_DPA_SRC_MAC,
			   ETH_ALEN, entry->l2_rewrite.eth_src))
		return -EMSGSIZE;
	if (!is_zero_ether_addr(entry->l2_rewrite.eth_dst) &&
	    rocker_tlv_put(desc_info, ROCKER_TLV_OF_DPA_DST_MAC,
			   ETH_ALEN, entry->l2_rewrite.eth_dst))
		return -EMSGSIZE;
	if (entry->l2_rewrite.vlan_id &&
	    rocker_tlv_put_be16(desc_info, ROCKER_TLV_OF_DPA_VLAN_ID,
				entry->l2_rewrite.vlan_id))
		return -EMSGSIZE;

	return 0;
}
