wsm_configuration(struct cw1200_common *priv, struct wsm_configuration *arg)
{
	int ret;
	struct wsm_buf *buf = &priv->wsm_cmd_buf;

	wsm_cmd_lock(priv);

	WSM_PUT32(buf, arg->dot11MaxTransmitMsduLifeTime);
	WSM_PUT32(buf, arg->dot11MaxReceiveLifeTime);
	WSM_PUT32(buf, arg->dot11RtsThreshold);


	WSM_PUT16(buf, arg->dpdData_size + 12);
	WSM_PUT16(buf, 1);
	WSM_PUT(buf, arg->dot11StationId, ETH_ALEN);
	WSM_PUT16(buf, 5);
	WSM_PUT(buf, arg->dpdData, arg->dpdData_size);

	ret = wsm_cmd_send(priv, buf, arg,
			   WSM_CONFIGURATION_REQ_ID, WSM_CMD_TIMEOUT);

	wsm_cmd_unlock(priv);
	return ret;

nomem:
	wsm_cmd_unlock(priv);
	return -ENOMEM;
}
