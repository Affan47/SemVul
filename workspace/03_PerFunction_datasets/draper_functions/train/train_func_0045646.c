dhcp6_start (NMDevice *self,
             NMConnection *connection,
             guint32 dhcp_opt,
             NMDeviceStateReason *reason)
{
	NMDevicePrivate *priv = NM_DEVICE_GET_PRIVATE (self);
	NMActStageReturn ret = NM_ACT_STAGE_RETURN_FAILURE;
	guint8 *anycast = NULL;
	GByteArray *tmp = NULL;
	guint hwaddr_len = 0;
	const guint8 *hwaddr;

	if (!connection) {
		connection = nm_device_get_connection (self);
		g_assert (connection);
	}


	if (priv->dhcp_anycast_address)
		anycast = priv->dhcp_anycast_address->data;


	if (priv->dhcp6_config)
		g_object_unref (priv->dhcp6_config);
	priv->dhcp6_config = nm_dhcp6_config_new ();

	g_warn_if_fail (priv->dhcp6_ip6_config == NULL);
	if (priv->dhcp6_ip6_config) {
		g_object_unref (priv->dhcp6_ip6_config);
		priv->dhcp6_ip6_config = NULL;
	}

	hwaddr = nm_device_get_hw_address (self, &hwaddr_len);
	if (hwaddr) {
		tmp = g_byte_array_sized_new (hwaddr_len);
		g_byte_array_append (tmp, hwaddr, hwaddr_len);
	}

	priv->dhcp6_client = nm_dhcp_manager_start_ip6 (priv->dhcp_manager,
	                                                nm_device_get_ip_iface (self),
	                                                tmp,
	                                                nm_connection_get_uuid (connection),
	                                                nm_connection_get_setting_ip6_config (connection),
	                                                priv->dhcp_timeout,
	                                                anycast,
	                                                (dhcp_opt == IP6_DHCP_OPT_OTHERCONF) ? TRUE : FALSE);
	if (tmp)
		g_byte_array_free (tmp, TRUE);

	if (priv->dhcp6_client) {
		priv->dhcp6_state_sigid = g_signal_connect (priv->dhcp6_client,
		                                            "state-changed",
		                                            G_CALLBACK (dhcp6_state_changed),
		                                            self);
		priv->dhcp6_timeout_sigid = g_signal_connect (priv->dhcp6_client,
		                                              "timeout",
		                                              G_CALLBACK (dhcp6_timeout),
		                                              self);


		ret = NM_ACT_STAGE_RETURN_POSTPONE;
	} else {
		*reason = NM_DEVICE_STATE_REASON_DHCP_START_FAILED;
		ret = NM_ACT_STAGE_RETURN_FAILURE;
	}

	return ret;
}
