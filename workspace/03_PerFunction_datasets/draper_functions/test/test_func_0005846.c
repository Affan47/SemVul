ath9k_regwrite(void *hw_priv, u32 val, u32 reg_offset)
{
	struct ath_hw *ah = (struct ath_hw *) hw_priv;
	struct ath_common *common = ath9k_hw_common(ah);
	struct ath9k_htc_priv *priv = (struct ath9k_htc_priv *) common->priv;

	if (atomic_read(&priv->wmi->mwrite_cnt))
		ath9k_regwrite_buffer(hw_priv, val, reg_offset);
	else
		ath9k_regwrite_single(hw_priv, val, reg_offset);
}
