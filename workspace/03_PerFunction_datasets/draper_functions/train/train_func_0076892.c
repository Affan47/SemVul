get_chassisguid(ibnd_node_t * node)
{
	uint32_t vendid = mad_get_field(node->info, 0, IB_NODE_VENDORID_F);
	uint64_t sysimgguid =
	    mad_get_field64(node->info, 0, IB_NODE_SYSTEM_GUID_F);

	if (vendid == TS_VENDOR_ID || vendid == SS_VENDOR_ID)
		return topspin_chassisguid(sysimgguid);
	else if (vendid == XS_VENDOR_ID || ibnd_is_xsigo_guid(sysimgguid))
		return xsigo_chassisguid(node);
	else
		return sysimgguid;
}
