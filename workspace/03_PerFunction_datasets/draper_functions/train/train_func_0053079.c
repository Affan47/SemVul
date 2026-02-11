iwl_find_disconn_antenna(struct iwl_priv *priv, u32* average_sig,
				     struct iwl_chain_noise_data *data)
{
	u32 active_chains = 0;
	u32 max_average_sig;
	u16 max_average_sig_antenna_i;
	u8 num_tx_chains;
	u8 first_chain;
	u16 i = 0;

	average_sig[0] = data->chain_signal_a / IWL_CAL_NUM_BEACONS;
	average_sig[1] = data->chain_signal_b / IWL_CAL_NUM_BEACONS;
	average_sig[2] = data->chain_signal_c / IWL_CAL_NUM_BEACONS;

	if (average_sig[0] >= average_sig[1]) {
		max_average_sig = average_sig[0];
		max_average_sig_antenna_i = 0;
		active_chains = (1 << max_average_sig_antenna_i);
	} else {
		max_average_sig = average_sig[1];
		max_average_sig_antenna_i = 1;
		active_chains = (1 << max_average_sig_antenna_i);
	}

	if (average_sig[2] >= max_average_sig) {
		max_average_sig = average_sig[2];
		max_average_sig_antenna_i = 2;
		active_chains = (1 << max_average_sig_antenna_i);
	}

	IWL_DEBUG_CALIB(priv, "average_sig: a %d b %d c %d\n",
		     average_sig[0], average_sig[1], average_sig[2]);
	IWL_DEBUG_CALIB(priv, "max_average_sig = %d, antenna %d\n",
		     max_average_sig, max_average_sig_antenna_i);


	for (i = 0; i < NUM_RX_CHAINS; i++) {
		if (i != max_average_sig_antenna_i) {
			s32 rssi_delta = (max_average_sig - average_sig[i]);


			if (rssi_delta > MAXIMUM_ALLOWED_PATHLOSS)
				data->disconn_array[i] = 1;
			else
				active_chains |= (1 << i);
			IWL_DEBUG_CALIB(priv, "i = %d  rssiDelta = %d  "
			     "disconn_array[i] = %d\n",
			     i, rssi_delta, data->disconn_array[i]);
		}
	}


	active_chains &= priv->nvm_data->valid_rx_ant;

	num_tx_chains = 0;
	for (i = 0; i < NUM_RX_CHAINS; i++) {


		u8 ant_msk = (1 << i);
		if (!(priv->nvm_data->valid_tx_ant & ant_msk))
			continue;

		num_tx_chains++;
		if (data->disconn_array[i] == 0)

			break;
		if (num_tx_chains == priv->hw_params.tx_chains_num &&
		    data->disconn_array[i]) {


			first_chain =
				find_first_chain(priv->nvm_data->valid_tx_ant);
			data->disconn_array[first_chain] = 0;
			active_chains |= BIT(first_chain);
			IWL_DEBUG_CALIB(priv,
					"All Tx chains are disconnected W/A - declare %d as connected\n",
					first_chain);
			break;
		}
	}

	if (active_chains != priv->nvm_data->valid_rx_ant &&
	    active_chains != priv->chain_noise_data.active_chains)
		IWL_DEBUG_CALIB(priv,
				"Detected that not all antennas are connected! "
				"Connected: %#x, valid: %#x.\n",
				active_chains,
				priv->nvm_data->valid_rx_ant);


	data->active_chains = active_chains;
	IWL_DEBUG_CALIB(priv, "active_chains (bitwise) = 0x%x\n",
			active_chains);
}
