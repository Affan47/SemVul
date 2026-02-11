rocker_event_process(const struct rocker *rocker,
				const struct rocker_desc_info *desc_info)
{
	const struct rocker_tlv *attrs[ROCKER_TLV_EVENT_MAX + 1];
	const struct rocker_tlv *info;
	u16 type;

	rocker_tlv_parse_desc(attrs, ROCKER_TLV_EVENT_MAX, desc_info);
	if (!attrs[ROCKER_TLV_EVENT_TYPE] ||
	    !attrs[ROCKER_TLV_EVENT_INFO])
		return -EIO;

	type = rocker_tlv_get_u16(attrs[ROCKER_TLV_EVENT_TYPE]);
	info = attrs[ROCKER_TLV_EVENT_INFO];

	switch (type) {
	case ROCKER_TLV_EVENT_TYPE_LINK_CHANGED:
		return rocker_event_link_change(rocker, info);
	case ROCKER_TLV_EVENT_TYPE_MAC_VLAN_SEEN:
		return rocker_event_mac_vlan_seen(rocker, info);
	}

	return -EOPNOTSUPP;
}
