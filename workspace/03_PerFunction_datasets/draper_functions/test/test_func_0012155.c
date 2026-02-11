netdev_fetch_busid ( struct net_device *netdev, void *data,
				size_t len ) {
	struct device_description *desc = &netdev->dev->desc;
	struct dhcp_netdev_desc dhcp_desc;

	dhcp_desc.type = desc->bus_type;
	dhcp_desc.vendor = htons ( desc->vendor );
	dhcp_desc.device = htons ( desc->device );
	if ( len > sizeof ( dhcp_desc ) )
		len = sizeof ( dhcp_desc );
	memcpy ( data, &dhcp_desc, len );
	return sizeof ( dhcp_desc );
}
