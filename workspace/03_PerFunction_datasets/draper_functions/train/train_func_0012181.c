lgs8gxx_read_signal_agc(struct lgs8gxx_state *priv, u16 *signal)
{
	u16 v;
	u8 agc_lvl[2], cat;

	dprintk("%s()\n", __func__);
	lgs8gxx_read_reg(priv, 0x3F, &agc_lvl[0]);
	lgs8gxx_read_reg(priv, 0x3E, &agc_lvl[1]);

	v = agc_lvl[0];
	v <<= 8;
	v |= agc_lvl[1];

	dprintk("agc_lvl: 0x%04X\n", v);

	if (v < 0x100)
		cat = 0;
	else if (v < 0x190)
		cat = 5;
	else if (v < 0x2A8)
		cat = 4;
	else if (v < 0x381)
		cat = 3;
	else if (v < 0x400)
		cat = 2;
	else if (v == 0x400)
		cat = 1;
	else
		cat = 0;

	*signal = cat * 65535 / 5;

	return 0;
}
