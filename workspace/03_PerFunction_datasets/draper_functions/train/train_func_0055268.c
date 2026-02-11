config_reg_read(struct cw1200_common *priv, u32 *val)
{
	switch (priv->hw_type) {
	case HIF_9000_SILICON_VERSATILE: {
		u16 val16;
		int ret = cw1200_reg_read_16(priv,
					     ST90TDS_CONFIG_REG_ID,
					     &val16);
		if (ret < 0)
			return ret;
		*val = val16;
		return 0;
	}
	case HIF_8601_VERSATILE:
	case HIF_8601_SILICON:
	default:
		cw1200_reg_read_32(priv, ST90TDS_CONFIG_REG_ID, val);
		break;
	}
	return 0;
}
