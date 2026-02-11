orinoco_cache_fw(struct orinoco_private *priv, int ap)
{
	const struct firmware *fw_entry = NULL;
	const char *pri_fw;
	const char *fw;

	pri_fw = orinoco_fw[priv->firmware_type].pri_fw;
	if (ap)
		fw = orinoco_fw[priv->firmware_type].ap_fw;
	else
		fw = orinoco_fw[priv->firmware_type].sta_fw;

	if (pri_fw) {
		if (request_firmware(&fw_entry, pri_fw, priv->dev) == 0)
			priv->cached_pri_fw = fw_entry;
	}

	if (fw) {
		if (request_firmware(&fw_entry, fw, priv->dev) == 0)
			priv->cached_fw = fw_entry;
	}
}
