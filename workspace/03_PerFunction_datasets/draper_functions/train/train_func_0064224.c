oid_rt_get_total_rx_bytes_hdl(struct oid_par_priv
					  *poid_par_priv)
{
	struct _adapter *padapter = (struct _adapter *)
				    (poid_par_priv->adapter_context);

	if (poid_par_priv->type_of_oid != QUERY_OID)
		return RNDIS_STATUS_NOT_ACCEPTED;
	if (poid_par_priv->information_buf_len >= sizeof(u32)) {
		*(u32 *)poid_par_priv->information_buf =
					   padapter->recvpriv.rx_bytes;
		*poid_par_priv->bytes_rw = poid_par_priv->
					   information_buf_len;
	} else {
		return RNDIS_STATUS_INVALID_LENGTH;
	}
	return RNDIS_STATUS_SUCCESS;
}
