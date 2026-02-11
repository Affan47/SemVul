if_spi_host_to_card(struct lbs_private *priv,
				u8 type, u8 *buf, u16 nb)
{
	int err = 0;
	unsigned long flags;
	struct if_spi_card *card = priv->card;
	struct if_spi_packet *packet;
	u16 blen;

	lbs_deb_enter_args(LBS_DEB_SPI, "type %d, bytes %d", type, nb);

	if (nb == 0) {
		netdev_err(priv->dev, "%s: invalid size requested: %d\n",
			   __func__, nb);
		err = -EINVAL;
		goto out;
	}
	blen = ALIGN(nb, 4);
	packet = kzalloc(sizeof(struct if_spi_packet) + blen, GFP_ATOMIC);
	if (!packet) {
		err = -ENOMEM;
		goto out;
	}
	packet->blen = blen;
	memcpy(packet->buffer, buf, nb);
	memset(packet->buffer + nb, 0, blen - nb);

	switch (type) {
	case MVMS_CMD:
		priv->dnld_sent = DNLD_CMD_SENT;
		spin_lock_irqsave(&card->buffer_lock, flags);
		list_add_tail(&packet->list, &card->cmd_packet_list);
		spin_unlock_irqrestore(&card->buffer_lock, flags);
		break;
	case MVMS_DAT:
		priv->dnld_sent = DNLD_DATA_SENT;
		spin_lock_irqsave(&card->buffer_lock, flags);
		list_add_tail(&packet->list, &card->data_packet_list);
		spin_unlock_irqrestore(&card->buffer_lock, flags);
		break;
	default:
		kfree(packet);
		netdev_err(priv->dev, "can't transfer buffer of type %d\n",
			   type);
		err = -EINVAL;
		break;
	}


	queue_work(card->workqueue, &card->packet_work);
out:
	lbs_deb_leave_args(LBS_DEB_SPI, "err=%d", err);
	return err;
}
