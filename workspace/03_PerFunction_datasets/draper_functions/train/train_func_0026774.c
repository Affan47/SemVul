oid_rt_pro_efuse_map_hdl(struct oid_par_priv *poid_par_priv)
{
	struct _adapter *Adapter = (struct _adapter *)
				   (poid_par_priv->adapter_context);
	uint status = RNDIS_STATUS_SUCCESS;
	u8		*data;

	*poid_par_priv->bytes_rw = 0;
	if (poid_par_priv->information_buf_len < EFUSE_MAP_MAX_SIZE)
		return RNDIS_STATUS_INVALID_LENGTH;
	data = (u8 *)poid_par_priv->information_buf;
	if (poid_par_priv->type_of_oid == QUERY_OID) {
		if (r8712_efuse_map_read(Adapter, 0, EFUSE_MAP_MAX_SIZE, data))
			*poid_par_priv->bytes_rw = EFUSE_MAP_MAX_SIZE;
		else
			status = RNDIS_STATUS_FAILURE;
	} else {

		if (r8712_efuse_reg_init(Adapter)) {
			if (r8712_efuse_map_write(Adapter, 0,
			    EFUSE_MAP_MAX_SIZE, data))
				*poid_par_priv->bytes_rw = EFUSE_MAP_MAX_SIZE;
			else
				status = RNDIS_STATUS_FAILURE;
			r8712_efuse_reg_uninit(Adapter);
		} else {
			status = RNDIS_STATUS_FAILURE;
		}
	}
	return status;
}
