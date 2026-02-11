ath10k_wmi_10x_op_pull_svc_rdy_ev(struct ath10k *ar, struct sk_buff *skb,
				  struct wmi_svc_rdy_ev_arg *arg)
{
	struct wmi_10x_service_ready_event *ev;
	int i, n;

	if (skb->len < sizeof(*ev))
		return -EPROTO;

	ev = (void *)skb->data;
	skb_pull(skb, sizeof(*ev));
	arg->min_tx_power = ev->hw_min_tx_power;
	arg->max_tx_power = ev->hw_max_tx_power;
	arg->ht_cap = ev->ht_cap_info;
	arg->vht_cap = ev->vht_cap_info;
	arg->sw_ver0 = ev->sw_version;
	arg->phy_capab = ev->phy_capability;
	arg->num_rf_chains = ev->num_rf_chains;
	arg->eeprom_rd = ev->hal_reg_capabilities.eeprom_rd;
	arg->num_mem_reqs = ev->num_mem_reqs;
	arg->service_map = ev->wmi_service_bitmap;
	arg->service_map_len = sizeof(ev->wmi_service_bitmap);

	n = min_t(size_t, __le32_to_cpu(arg->num_mem_reqs),
		  ARRAY_SIZE(arg->mem_reqs));
	for (i = 0; i < n; i++)
		arg->mem_reqs[i] = &ev->mem_reqs[i];

	if (skb->len <
	    __le32_to_cpu(arg->num_mem_reqs) * sizeof(arg->mem_reqs[0]))
		return -EPROTO;

	return 0;
}
