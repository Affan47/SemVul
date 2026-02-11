brcms_c_up(struct brcms_c_info *wlc)
{
	struct ieee80211_channel *ch;

	brcms_dbg_info(wlc->hw->d11core, "wl%d\n", wlc->pub->unit);


	if (wlc->pub->hw_off || brcms_deviceremoved(wlc))
		return -ENOMEDIUM;

	if (!wlc->pub->hw_up) {
		brcms_b_hw_up(wlc->hw);
		wlc->pub->hw_up = true;
	}

	if ((wlc->pub->boardflags & BFL_FEM)
	    && (ai_get_chip_id(wlc->hw->sih) == BCMA_CHIP_ID_BCM4313)) {
		if (wlc->pub->boardrev >= 0x1250
		    && (wlc->pub->boardflags & BFL_FEM_BT))
			brcms_b_mhf(wlc->hw, MHF5, MHF5_4313_GPIOCTRL,
				MHF5_4313_GPIOCTRL, BRCM_BAND_ALL);
		else
			brcms_b_mhf(wlc->hw, MHF4, MHF4_EXTPA_ENABLE,
				    MHF4_EXTPA_ENABLE, BRCM_BAND_ALL);
	}


	if (!wlc->pub->radio_disabled) {
		int status = brcms_b_up_prep(wlc->hw);
		if (status == -ENOMEDIUM) {
			if (!mboolisset
			    (wlc->pub->radio_disabled, WL_RADIO_HW_DISABLE)) {
				struct brcms_bss_cfg *bsscfg = wlc->bsscfg;
				mboolset(wlc->pub->radio_disabled,
					 WL_RADIO_HW_DISABLE);
				if (bsscfg->type == BRCMS_TYPE_STATION ||
				    bsscfg->type == BRCMS_TYPE_ADHOC)
					brcms_err(wlc->hw->d11core,
						  "wl%d: up: rfdisable -> "
						  "bsscfg_disable()\n",
						   wlc->pub->unit);
			}
		}
	}

	if (wlc->pub->radio_disabled) {
		brcms_c_radio_monitor_start(wlc);
		return 0;
	}


	wlc->clk = true;

	brcms_c_radio_monitor_stop(wlc);


	brcms_b_mhf(wlc->hw, MHF1, MHF1_EDCF, MHF1_EDCF, BRCM_BAND_ALL);

	brcms_init(wlc->wl);
	wlc->pub->up = true;

	if (wlc->bandinit_pending) {
		ch = wlc->pub->ieee_hw->conf.chandef.chan;
		brcms_c_suspend_mac_and_wait(wlc);
		brcms_c_set_chanspec(wlc, ch20mhz_chspec(ch->hw_value));
		wlc->bandinit_pending = false;
		brcms_c_enable_mac(wlc);
	}

	brcms_b_up_finish(wlc->hw);


	brcms_c_wme_retries_write(wlc);


	brcms_add_timer(wlc->wdtimer, TIMER_INTERVAL_WATCHDOG, true);
	wlc->WDarmed = true;


	brcms_c_stf_phy_txant_upd(wlc);

	brcms_c_ht_update_ldpc(wlc, wlc->stf->ldpc);

	return 0;
}
