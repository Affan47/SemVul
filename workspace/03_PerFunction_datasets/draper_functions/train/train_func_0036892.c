tda998x_write_if(struct tda998x_priv *priv, u8 bit, u16 addr,
		 union hdmi_infoframe *frame)
{
	u8 buf[32];
	ssize_t len;

	len = hdmi_infoframe_pack(frame, buf, sizeof(buf));
	if (len < 0) {
		dev_err(&priv->hdmi->dev,
			"hdmi_infoframe_pack() type=0x%02x failed: %zd\n",
			frame->any.type, len);
		return;
	}

	reg_clear(priv, REG_DIP_IF_FLAGS, bit);
	reg_write_range(priv, addr, buf, len);
	reg_set(priv, REG_DIP_IF_FLAGS, bit);
}
