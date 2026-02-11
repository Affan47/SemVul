rcar_thermal_had_changed(struct rcar_thermal_priv *priv, u32 status)
{
	struct device *dev = rcar_priv_to_dev(priv);

	status = (status >> rcar_id_to_shift(priv)) & 0x3;

	if (status) {
		dev_dbg(dev, "thermal%d %s%s\n",
			priv->id,
			(status & 0x2) ? "Rising " : "",
			(status & 0x1) ? "Falling" : "");
	}

	return status;
}
