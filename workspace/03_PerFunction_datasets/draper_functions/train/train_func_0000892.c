garmin_write(struct tty_struct *tty, struct usb_serial_port *port,
					 const unsigned char *buf, int count)
{
	struct device *dev = &port->dev;
	int pktid, pktsiz, len;
	struct garmin_data *garmin_data_p = usb_get_serial_port_data(port);
	__le32 *privpkt = (__le32 *)garmin_data_p->privpkt;

	usb_serial_debug_data(dev, __func__, count, buf);

	if (garmin_data_p->state == STATE_RESET)
		return -EIO;


	if (count >= GARMIN_PKTHDR_LENGTH) {
		len = PRIVPKTSIZ;
		if (count < len)
			len = count;

		memcpy(garmin_data_p->privpkt, buf, len);

		pktsiz = getDataLength(garmin_data_p->privpkt);
		pktid  = getPacketId(garmin_data_p->privpkt);

		if (count == (GARMIN_PKTHDR_LENGTH+pktsiz)
		    && GARMIN_LAYERID_PRIVATE ==
				getLayerId(garmin_data_p->privpkt)) {

			dev_dbg(dev, "%s - processing private request %d\n",
				__func__, pktid);


			garmin_clear(garmin_data_p);

			switch (pktid) {
			case PRIV_PKTID_SET_MODE:
				if (pktsiz != 4)
					return -EINVPKT;
				garmin_data_p->mode = __le32_to_cpu(privpkt[3]);
				dev_dbg(dev, "%s - mode set to %d\n",
					__func__, garmin_data_p->mode);
				break;

			case PRIV_PKTID_INFO_REQ:
				priv_status_resp(port);
				break;

			case PRIV_PKTID_RESET_REQ:
				process_resetdev_request(port);
				break;

			case PRIV_PKTID_SET_DEF_MODE:
				if (pktsiz != 4)
					return -EINVPKT;
				initial_mode = __le32_to_cpu(privpkt[3]);
				dev_dbg(dev, "%s - initial_mode set to %d\n",
					__func__,
					garmin_data_p->mode);
				break;
			}
			return count;
		}
	}

	if (garmin_data_p->mode == MODE_GARMIN_SERIAL) {
		return gsp_receive(garmin_data_p, buf, count);
	} else {
		return nat_receive(garmin_data_p, buf, count);
	}
}
