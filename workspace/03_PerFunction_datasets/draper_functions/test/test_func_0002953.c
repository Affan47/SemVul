ib_sma_set_port_info ( struct ib_device *ibdev,
				  struct ib_mad_interface *mi,
				  union ib_mad *mad ) {
	const struct ib_port_info *port_info = &mad->smp.smp_data.port_info;
	unsigned int link_width_enabled;
	unsigned int link_speed_enabled;
	int rc;


	memcpy ( &ibdev->gid.s.prefix, port_info->gid_prefix,
		 sizeof ( ibdev->gid.s.prefix ) );
	ibdev->lid = ntohs ( port_info->lid );
	ibdev->sm_lid = ntohs ( port_info->mastersm_lid );
	if ( ( link_width_enabled = port_info->link_width_enabled ) )
		ibdev->link_width_enabled = link_width_enabled;
	if ( ( link_speed_enabled =
	       ( port_info->link_speed_active__link_speed_enabled & 0xf ) ) )
		ibdev->link_speed_enabled = link_speed_enabled;
	ibdev->sm_sl = ( port_info->neighbour_mtu__mastersm_sl & 0xf );
	DBGC ( mi, "SMA %p set LID %04x SMLID %04x link width %02x speed "
	       "%02x\n", mi, ibdev->lid, ibdev->sm_lid,
	       ibdev->link_width_enabled, ibdev->link_speed_enabled );


	if ( ( rc = ib_set_port_info ( ibdev, mad ) ) != 0 ) {
		DBGC ( mi, "SMA %p could not set port information: %s\n",
		       mi, strerror ( rc ) );
		return rc;
	}

	return 0;
}
