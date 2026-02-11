wl3501_rx_interrupt(struct net_device *dev)
{
	int morepkts;
	u16 addr;
	u8 sig_id;
	struct wl3501_card *this = netdev_priv(dev);

	pr_debug("entry");
loop:
	morepkts = 0;
	if (!wl3501_esbq_confirm(this))
		goto free;
	wl3501_get_from_wla(this, this->esbq_confirm, &addr, sizeof(addr));
	wl3501_get_from_wla(this, addr + 2, &sig_id, sizeof(sig_id));

	switch (sig_id) {
	case WL3501_SIG_DEAUTH_IND:
	case WL3501_SIG_DISASSOC_IND:
	case WL3501_SIG_ALARM:
		wl3501_alarm_interrupt(dev, this);
		break;
	case WL3501_SIG_MD_CONFIRM:
		wl3501_md_confirm_interrupt(dev, this, addr);
		break;
	case WL3501_SIG_MD_IND:
		wl3501_md_ind_interrupt(dev, this, addr);
		break;
	case WL3501_SIG_GET_CONFIRM:
		wl3501_get_confirm_interrupt(this, addr,
					     &this->sig_get_confirm,
					     sizeof(this->sig_get_confirm));
		break;
	case WL3501_SIG_PWR_MGMT_CONFIRM:
		wl3501_get_confirm_interrupt(this, addr,
					     &this->sig_pwr_mgmt_confirm,
					    sizeof(this->sig_pwr_mgmt_confirm));
		break;
	case WL3501_SIG_START_CONFIRM:
		wl3501_start_confirm_interrupt(dev, this, addr);
		break;
	case WL3501_SIG_SCAN_CONFIRM:
		wl3501_mgmt_scan_confirm(this, addr);
		break;
	case WL3501_SIG_JOIN_CONFIRM:
		wl3501_mgmt_join_confirm(dev, addr);
		break;
	case WL3501_SIG_ASSOC_CONFIRM:
		wl3501_assoc_confirm_interrupt(dev, addr);
		break;
	case WL3501_SIG_AUTH_CONFIRM:
		wl3501_auth_confirm_interrupt(this, addr);
		break;
	case WL3501_SIG_RESYNC_CONFIRM:
		wl3501_mgmt_resync(this);
		break;
	}
	wl3501_esbq_confirm_done(this);
	morepkts = 1;

free:
	wl3501_esbq_req_free(this);
	if (morepkts)
		goto loop;
}
