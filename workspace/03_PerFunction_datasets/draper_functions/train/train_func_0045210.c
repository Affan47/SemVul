rndis_wlan_indication(struct usbnet *usbdev, void *ind, int buflen)
{
	struct rndis_wlan_private *priv = get_rndis_wlan_priv(usbdev);
	struct rndis_indicate *msg = ind;

	switch (le32_to_cpu(msg->status)) {
	case RNDIS_STATUS_MEDIA_CONNECT:
		if (priv->current_command_oid == RNDIS_OID_802_11_ADD_KEY) {


			netdev_dbg(usbdev->net, "ignored RNDIS_OID_802_11_ADD_KEY triggered 'media connect'\n");
			return;
		}

		usbnet_pause_rx(usbdev);

		netdev_info(usbdev->net, "media connect\n");


		set_bit(WORK_LINK_UP, &priv->work_pending);
		queue_work(priv->workqueue, &priv->work);
		break;

	case RNDIS_STATUS_MEDIA_DISCONNECT:
		netdev_info(usbdev->net, "media disconnect\n");


		set_bit(WORK_LINK_DOWN, &priv->work_pending);
		queue_work(priv->workqueue, &priv->work);
		break;

	case RNDIS_STATUS_MEDIA_SPECIFIC_INDICATION:
		rndis_wlan_media_specific_indication(usbdev, msg, buflen);
		break;

	default:
		netdev_info(usbdev->net, "indication: 0x%08x\n",
			    le32_to_cpu(msg->status));
		break;
	}
}
