alps_update_btn_info_ss4_v2(unsigned char otp[][4],
				       struct alps_data *priv)
{
	unsigned char is_btnless;

	if (IS_SS4PLUS_DEV(priv->dev_id))
		is_btnless = (otp[1][0] >> 1) & 0x01;
	else
		is_btnless = (otp[1][1] >> 3) & 0x01;

	if (is_btnless)
		priv->flags |= ALPS_BUTTONPAD;

	return 0;
}
