il_power_set_mode(struct il_priv *il, struct il_powertable_cmd *cmd, bool force)
{
	int ret;
	bool update_chains;

	lockdep_assert_held(&il->mutex);


	update_chains = il->chain_noise_data.state == IL_CHAIN_NOISE_DONE ||
	    il->chain_noise_data.state == IL_CHAIN_NOISE_ALIVE;

	if (!memcmp(&il->power_data.sleep_cmd, cmd, sizeof(*cmd)) && !force)
		return 0;

	if (!il_is_ready_rf(il))
		return -EIO;


	memcpy(&il->power_data.sleep_cmd_next, cmd, sizeof(*cmd));
	if (test_bit(S_SCANNING, &il->status) && !force) {
		D_INFO("Defer power set mode while scanning\n");
		return 0;
	}

	if (cmd->flags & IL_POWER_DRIVER_ALLOW_SLEEP_MSK)
		set_bit(S_POWER_PMI, &il->status);

	ret = il_set_power(il, cmd);
	if (!ret) {
		if (!(cmd->flags & IL_POWER_DRIVER_ALLOW_SLEEP_MSK))
			clear_bit(S_POWER_PMI, &il->status);

		if (il->ops->update_chain_flags && update_chains)
			il->ops->update_chain_flags(il);
		else if (il->ops->update_chain_flags)
			D_POWER("Cannot update the power, chain noise "
				"calibration running: %d\n",
				il->chain_noise_data.state);

		memcpy(&il->power_data.sleep_cmd, cmd, sizeof(*cmd));
	} else
		IL_ERR("set power fail, ret = %d", ret);

	return ret;
}
