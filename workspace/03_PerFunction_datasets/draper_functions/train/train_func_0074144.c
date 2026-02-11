oid_rt_set_channelplan_hdl(struct oid_par_priv
				       *poid_par_priv)
{
	struct _adapter *padapter = (struct _adapter *)
				    (poid_par_priv->adapter_context);
	struct eeprom_priv *peeprompriv = &padapter->eeprompriv;

	if (poid_par_priv->type_of_oid != SET_OID)
		return RNDIS_STATUS_NOT_ACCEPTED;
	peeprompriv->channel_plan = *(u16 *)poid_par_priv->information_buf;
	return RNDIS_STATUS_SUCCESS;
}
