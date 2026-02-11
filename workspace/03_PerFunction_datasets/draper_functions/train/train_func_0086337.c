iwl_bg_ct_enter(struct work_struct *work)
{
	struct iwl_priv *priv = container_of(work, struct iwl_priv, ct_enter);
	struct iwl_tt_mgmt *tt = &priv->thermal_throttle;

	if (test_bit(STATUS_EXIT_PENDING, &priv->status))
		return;

	if (!iwl_is_ready(priv))
		return;

	if (tt->state != IWL_TI_CT_KILL) {
		IWL_ERR(priv, "Device reached critical temperature "
			      "- ucode going to sleep!\n");
		if (!priv->thermal_throttle.advanced_tt)
			iwl_legacy_tt_handler(priv,
					      IWL_MINIMAL_POWER_THRESHOLD,
					      true);
		else
			iwl_advance_tt_handler(priv,
					       CT_KILL_THRESHOLD + 1, true);
	}
}
