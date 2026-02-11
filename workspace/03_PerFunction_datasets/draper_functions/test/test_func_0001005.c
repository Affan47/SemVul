helper_firmware_cb(const struct firmware *firmware, void *context)
{
	struct lbs_private *priv = context;

	if (!firmware) {

		load_next_firmware_from_table(priv);
		return;
	}


	if (priv->fw_iter->fwname) {
		priv->helper_fw = firmware;
		do_load_firmware(priv, priv->fw_iter->fwname, main_firmware_cb);
	} else {

		lbs_fw_loaded(priv, 0, firmware, NULL);
	}
}
