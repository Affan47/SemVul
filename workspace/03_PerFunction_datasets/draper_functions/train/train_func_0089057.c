iwlagn_rx_missed_beacon_notif(struct iwl_priv *priv,
					  struct iwl_rx_cmd_buffer *rxb)

{
	struct iwl_rx_packet *pkt = rxb_addr(rxb);
	struct iwl_missed_beacon_notif *missed_beacon = (void *)pkt->data;

	if (le32_to_cpu(missed_beacon->consecutive_missed_beacons) >
	    priv->missed_beacon_threshold) {
		IWL_DEBUG_CALIB(priv,
		    "missed bcn cnsq %d totl %d rcd %d expctd %d\n",
		    le32_to_cpu(missed_beacon->consecutive_missed_beacons),
		    le32_to_cpu(missed_beacon->total_missed_becons),
		    le32_to_cpu(missed_beacon->num_recvd_beacons),
		    le32_to_cpu(missed_beacon->num_expected_beacons));
		if (!test_bit(STATUS_SCANNING, &priv->status))
			iwl_init_sensitivity(priv);
	}
}
