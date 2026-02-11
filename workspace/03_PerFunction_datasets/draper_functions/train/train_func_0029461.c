ibcc_bind(
	IN ibcc_t* const p_ibcc)
{
	ib_api_status_t status = IB_SUCCESS;

	OSM_LOG_ENTER(&(IbisObj.log));


	if ((status = ibis_gsi_mad_ctrl_bind(
			&(IbisObj.mad_ctrl),
			IB_MCLASS_CC, 2,
			&p_ibcc->lid_route_bind)) != IB_SUCCESS)
		goto Exit;


	if ((status = ibis_gsi_mad_ctrl_set_class_attr_cb(
			&(IbisObj.mad_ctrl),
			IB_MCLASS_CC,
			CL_NTOH16(IB_MAD_ATTR_CLASS_PORT_INFO),
			ibis_gsi_sync_mad_batch_callback,
			(void *)p_ibcc)) != IB_SUCCESS)
		goto Exit;


	if ((status = ibis_gsi_mad_ctrl_set_class_attr_cb(
			&(IbisObj.mad_ctrl),
			IB_MCLASS_CC,
			CL_NTOH16(IB_MAD_ATTR_NOTICE),
			ibis_gsi_sync_mad_batch_callback,
			(void *)p_ibcc)) != IB_SUCCESS)
		goto Exit;


	if ((status = ibis_gsi_mad_ctrl_set_class_attr_cb(
			&(IbisObj.mad_ctrl),
			IB_MCLASS_CC,
			CL_NTOH16(IB_MAD_ATTR_CONG_INFO),
			ibis_gsi_sync_mad_batch_callback,
			(void *)p_ibcc)) != IB_SUCCESS)
		goto Exit;


	if ((status = ibis_gsi_mad_ctrl_set_class_attr_cb(
			&(IbisObj.mad_ctrl),
			IB_MCLASS_CC,
			CL_NTOH16(IB_MAD_ATTR_CONG_KEY_INFO),
			ibis_gsi_sync_mad_batch_callback,
			(void *)p_ibcc)) != IB_SUCCESS)
		goto Exit;


	if ((status = ibis_gsi_mad_ctrl_set_class_attr_cb(
			&(IbisObj.mad_ctrl),
			IB_MCLASS_CC,
			CL_NTOH16(IB_MAD_ATTR_CONG_LOG),
			ibis_gsi_sync_mad_batch_callback,
			(void *)p_ibcc)) != IB_SUCCESS)
		goto Exit;


	if ((status = ibis_gsi_mad_ctrl_set_class_attr_cb(
			&(IbisObj.mad_ctrl),
			IB_MCLASS_CC,
			CL_NTOH16(IB_MAD_ATTR_SW_CONG_SETTING),
			ibis_gsi_sync_mad_batch_callback,
			(void *)p_ibcc)) != IB_SUCCESS)
		goto Exit;


	if ((status = ibis_gsi_mad_ctrl_set_class_attr_cb(
			&(IbisObj.mad_ctrl),
			IB_MCLASS_CC,
			CL_NTOH16(IB_MAD_ATTR_SW_PORT_CONG_SETTING),
			ibis_gsi_sync_mad_batch_callback,
			(void *)p_ibcc)) != IB_SUCCESS)
		goto Exit;


	if ((status = ibis_gsi_mad_ctrl_set_class_attr_cb(
			&(IbisObj.mad_ctrl),
			IB_MCLASS_CC,
			CL_NTOH16(IB_MAD_ATTR_CA_CONG_SETTING),
			ibis_gsi_sync_mad_batch_callback,
			(void *)p_ibcc)) != IB_SUCCESS)
		goto Exit;


	if ((status = ibis_gsi_mad_ctrl_set_class_attr_cb(
			&(IbisObj.mad_ctrl),
			IB_MCLASS_CC,
			CL_NTOH16(IB_MAD_ATTR_CC_TBL),
			ibis_gsi_sync_mad_batch_callback,
			(void *)p_ibcc)) != IB_SUCCESS)
		goto Exit;


	if ((status = ibis_gsi_mad_ctrl_set_class_attr_cb(
			&(IbisObj.mad_ctrl),
			IB_MCLASS_CC,
			CL_NTOH16(IB_MAD_ATTR_TIME_STAMP),
			ibis_gsi_sync_mad_batch_callback,
			(void *)p_ibcc)) != IB_SUCCESS)
		goto Exit;

    Exit :
	OSM_LOG_EXIT( &(IbisObj.log) );
	return status;
}
