i40e_set_lan_rx_queue_context(struct i40e_hw *hw,
						    u16 queue,
						    struct i40e_hmc_obj_rxq *s)
{
	i40e_status err;
	u8 *context_bytes;

	err = i40e_hmc_get_object_va(&hw->hmc, &context_bytes,
				     I40E_HMC_LAN_RX, queue);
	if (err < 0)
		return err;

	return i40e_set_hmc_context(context_bytes,
				    i40e_hmc_rxq_ce_info, (u8 *)s);
}
