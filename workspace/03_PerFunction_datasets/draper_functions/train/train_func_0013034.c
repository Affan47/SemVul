orinoco_reinit_firmware(struct orinoco_private *priv)
{
	struct hermes *hw = &priv->hw;
	int err;

	err = hw->ops->init(hw);
	if (priv->do_fw_download && !err) {
		err = orinoco_download(priv);
		if (err)
			priv->do_fw_download = 0;
	}
	if (!err)
		err = orinoco_hw_allocate_fid(priv);

	return err;
}
