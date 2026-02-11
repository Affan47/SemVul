if_usb_setup_firmware(struct lbtf_private *priv)
{
	struct if_usb_card *cardp = priv->card;
	struct cmd_ds_set_boot2_ver b2_cmd;

	lbtf_deb_enter(LBTF_DEB_USB);

	if_usb_submit_rx_urb(cardp);
	b2_cmd.hdr.size = cpu_to_le16(sizeof(b2_cmd));
	b2_cmd.action = 0;
	b2_cmd.version = cardp->boot2_version;

	if (lbtf_cmd_with_response(priv, CMD_SET_BOOT2_VER, &b2_cmd))
		lbtf_deb_usb("Setting boot2 version failed\n");

	lbtf_deb_leave(LBTF_DEB_USB);
}
