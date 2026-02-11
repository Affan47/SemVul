lgs8g75_set_adc_vpp(struct lgs8gxx_state *priv,
	u8 sel)
{
	u8 r26 = 0x73, r27 = 0x90;

	if (priv->config->prod != LGS8GXX_PROD_LGS8G75)
		return 0;

	r26 |= (sel & 0x01) << 7;
	r27 |= (sel & 0x02) >> 1;
	lgs8gxx_write_reg(priv, 0x26, r26);
	lgs8gxx_write_reg(priv, 0x27, r27);

	return 0;
}
