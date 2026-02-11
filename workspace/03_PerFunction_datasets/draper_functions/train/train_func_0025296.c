ath6kl_disconnect(struct ath6kl_vif *vif)
{
	if (test_bit(CONNECTED, &vif->flags) ||
	    test_bit(CONNECT_PEND, &vif->flags)) {
		ath6kl_wmi_disconnect_cmd(vif->ar->wmi, vif->fw_vif_idx);


		clear_bit(CONNECT_PEND, &vif->flags);
	}
}
