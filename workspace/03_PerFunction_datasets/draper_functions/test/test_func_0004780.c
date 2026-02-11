ib_smc_mad ( struct ib_device *ibdev, uint16_t attr_id,
			uint32_t attr_mod, ib_local_mad_t local_mad,
			union ib_mad *mad ) {
	int rc;


	memset ( mad, 0, sizeof ( *mad ) );
	mad->hdr.base_version = IB_MGMT_BASE_VERSION;
	mad->hdr.mgmt_class = IB_MGMT_CLASS_SUBN_LID_ROUTED;
	mad->hdr.class_version = 1;
	mad->hdr.method = IB_MGMT_METHOD_GET;
	mad->hdr.attr_id = attr_id;
	mad->hdr.attr_mod = attr_mod;


	if ( ( rc = local_mad ( ibdev, mad ) ) != 0 )
		return rc;

	return 0;
}
