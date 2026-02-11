bnx2x_dcbx_get_ap_feature(struct bnx2x *bp,
				   struct dcbx_app_priority_feature *app,
				   u32 error) {
	u8 index;
	u32 *ttp = bp->dcbx_port_params.app.traffic_type_priority;

	if (GET_FLAGS(error, DCBX_LOCAL_APP_ERROR))
		DP(BNX2X_MSG_DCB, "DCBX_LOCAL_APP_ERROR\n");

	if (GET_FLAGS(error, DCBX_LOCAL_APP_MISMATCH))
		DP(BNX2X_MSG_DCB, "DCBX_LOCAL_APP_MISMATCH\n");

	if (GET_FLAGS(error, DCBX_REMOTE_APP_TLV_NOT_FOUND))
		DP(BNX2X_MSG_DCB, "DCBX_REMOTE_APP_TLV_NOT_FOUND\n");
	if (app->enabled &&
	    !GET_FLAGS(error, DCBX_LOCAL_APP_ERROR | DCBX_LOCAL_APP_MISMATCH |
			      DCBX_REMOTE_APP_TLV_NOT_FOUND)) {

		bp->dcbx_port_params.app.enabled = true;

		for (index = 0 ; index < LLFC_DRIVER_TRAFFIC_TYPE_MAX; index++)
			ttp[index] = 0;

		if (app->default_pri < MAX_PFC_PRIORITIES)
			ttp[LLFC_TRAFFIC_TYPE_NW] = app->default_pri;

		for (index = 0 ; index < DCBX_MAX_APP_PROTOCOL; index++) {
			struct dcbx_app_priority_entry *entry =
							app->app_pri_tbl;

			if (GET_FLAGS(entry[index].appBitfield,
				     DCBX_APP_SF_ETH_TYPE) &&
			   ETH_TYPE_FCOE == entry[index].app_id)
				bnx2x_dcbx_get_ap_priority(bp,
						entry[index].pri_bitmap,
						LLFC_TRAFFIC_TYPE_FCOE);

			if (GET_FLAGS(entry[index].appBitfield,
				     DCBX_APP_SF_PORT) &&
			   TCP_PORT_ISCSI == entry[index].app_id)
				bnx2x_dcbx_get_ap_priority(bp,
						entry[index].pri_bitmap,
						LLFC_TRAFFIC_TYPE_ISCSI);
		}
	} else {
		DP(BNX2X_MSG_DCB, "DCBX_LOCAL_APP_DISABLED\n");
		bp->dcbx_port_params.app.enabled = false;
		for (index = 0 ; index < LLFC_DRIVER_TRAFFIC_TYPE_MAX; index++)
			ttp[index] = INVALID_TRAFFIC_TYPE_PRIORITY;
	}
}
