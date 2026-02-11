orinoco_clear_tkip_key(struct orinoco_private *priv, int key_idx)
{
	struct hermes *hw = &priv->hw;
	int err;

	err = hermes_write_wordrec(hw, USER_BAP,
				   HERMES_RID_CNFREMDEFAULTTKIPKEY_AGERE,
				   key_idx);
	if (err)
		printk(KERN_WARNING "%s: Error %d clearing TKIP key %d\n",
		       priv->ndev->name, err, key_idx);
	return err;
}
