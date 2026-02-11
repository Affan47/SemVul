load_next_firmware_from_table(struct lbs_private *priv)
{
	const struct lbs_fw_table *iter;

	if (!priv->fw_iter)
		iter = priv->fw_table;
	else
		iter = ++priv->fw_iter;

	if (priv->helper_fw) {
		release_firmware(priv->helper_fw);
		priv->helper_fw = NULL;
	}

next:
	if (!iter->helper) {

		lbs_fw_loaded(priv, -ENOENT, NULL, NULL);
		return;
	}

	if (iter->model != priv->fw_model) {
		iter++;
		goto next;
	}

	priv->fw_iter = iter;
	do_load_firmware(priv, iter->helper, helper_firmware_cb);
}
