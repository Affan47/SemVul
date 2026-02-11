oid_rt_get_channelplan_hdl(struct oid_par_priv *poid_par_priv)
{
	struct _adapter *padapter = (struct _adapter *)
				    (poid_par_priv->adapter_context);
	struct eeprom_priv *peeprompriv = &padapter->eeprompriv;

	if (poid_par_priv->type_of_oid != QUERY_OID)
		return RNDIS_STATUS_NOT_ACCEPTED;
	*poid_par_priv->bytes_rw = poid_par_priv->information_buf_len;
	*(u16 *)poid_par_priv->information_buf = peeprompriv->channel_plan;
	return RNDIS_STATUS_SUCCESS;
}
