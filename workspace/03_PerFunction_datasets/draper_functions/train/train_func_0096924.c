orinoco_hw_get_bitratelist(struct orinoco_private *priv,
			       int *numrates, s32 *rates, int max)
{
	struct hermes *hw = &priv->hw;
	struct hermes_idstring list;
	unsigned char *p = (unsigned char *)&list.val;
	int err = 0;
	int num;
	int i;
	unsigned long flags;

	if (orinoco_lock(priv, &flags) != 0)
		return -EBUSY;

	err = hw->ops->read_ltv(hw, USER_BAP, HERMES_RID_SUPPORTEDDATARATES,
				sizeof(list), NULL, &list);
	orinoco_unlock(priv, &flags);

	if (err)
		return err;

	num = le16_to_cpu(list.len);
	*numrates = num;
	num = min(num, max);

	for (i = 0; i < num; i++)
		rates[i] = (p[i] & 0x7f) * 500000;

	return 0;
}
