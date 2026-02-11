disable_all_objs(const struct cc770_priv *priv)
{
	int o, mo;

	for (o = 0; o <  ARRAY_SIZE(priv->obj_flags); o++) {
		mo = obj2msgobj(o);

		if (priv->obj_flags[o] & CC770_OBJ_FLAG_RX) {
			if (o > 0 && priv->control_normal_mode & CTRL_EAF)
				continue;

			cc770_write_reg(priv, msgobj[mo].ctrl1,
					NEWDAT_RES | MSGLST_RES |
					TXRQST_RES | RMTPND_RES);
			cc770_write_reg(priv, msgobj[mo].ctrl0,
					MSGVAL_RES | TXIE_RES |
					RXIE_RES | INTPND_RES);
		} else {

			cc770_write_reg(priv, msgobj[mo].ctrl1,
					RMTPND_RES | TXRQST_RES |
					CPUUPD_RES | NEWDAT_RES);
			cc770_write_reg(priv, msgobj[mo].ctrl0,
					MSGVAL_RES | TXIE_RES |
					RXIE_RES | INTPND_RES);
		}
	}
}
