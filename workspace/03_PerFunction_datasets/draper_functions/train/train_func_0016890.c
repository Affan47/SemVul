il3945_rfkill_poll(struct work_struct *data)
{
	struct il_priv *il =
	    container_of(data, struct il_priv, _3945.rfkill_poll.work);
	bool old_rfkill = test_bit(S_RFKILL, &il->status);
	bool new_rfkill =
	    !(_il_rd(il, CSR_GP_CNTRL) & CSR_GP_CNTRL_REG_FLAG_HW_RF_KILL_SW);

	if (new_rfkill != old_rfkill) {
		if (new_rfkill)
			set_bit(S_RFKILL, &il->status);
		else
			clear_bit(S_RFKILL, &il->status);

		wiphy_rfkill_set_hw_state(il->hw->wiphy, new_rfkill);

		D_RF_KILL("RF_KILL bit toggled to %s.\n",
			  new_rfkill ? "disable radio" : "enable radio");
	}


	queue_delayed_work(il->workqueue, &il->_3945.rfkill_poll,
			   round_jiffies_relative(2 * HZ));

}
