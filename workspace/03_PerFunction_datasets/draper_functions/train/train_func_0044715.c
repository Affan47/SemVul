hv_get_dev_type(const struct vmbus_channel *channel)
{
	const uuid_le *guid = &channel->offermsg.offer.if_type;
	u16 i;

	if (is_hvsock_channel(channel) || is_unsupported_vmbus_devs(guid))
		return HV_UNKOWN;

	for (i = HV_IDE; i < HV_UNKOWN; i++) {
		if (!uuid_le_cmp(*guid, vmbus_devs[i].guid))
			return i;
	}
	pr_info("Unknown GUID: %pUl\n", guid);
	return i;
}
