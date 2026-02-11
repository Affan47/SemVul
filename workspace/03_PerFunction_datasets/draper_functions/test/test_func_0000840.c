i40e_ptp_init(struct i40e_pf *pf)
{
	struct net_device *netdev = pf->vsi[pf->lan_vsi]->netdev;
	struct i40e_hw *hw = &pf->hw;
	u32 pf_id;
	long err;


	pf_id = (rd32(hw, I40E_PRTTSYN_CTL0) & I40E_PRTTSYN_CTL0_PF_ID_MASK) >>
		I40E_PRTTSYN_CTL0_PF_ID_SHIFT;
	if (hw->pf_id != pf_id) {
		pf->flags &= ~I40E_FLAG_PTP;
		dev_info(&pf->pdev->dev, "%s: PTP not supported on %s\n",
			 __func__,
			 netdev->name);
		return;
	}


	spin_lock_init(&pf->tmreg_lock);


	err = i40e_ptp_create_clock(pf);
	if (err) {
		pf->ptp_clock = NULL;
		dev_err(&pf->pdev->dev, "%s: ptp_clock_register failed\n",
			__func__);
	} else {
		struct timespec64 ts;
		u32 regval;

		if (pf->hw.debug_mask & I40E_DEBUG_LAN)
			dev_info(&pf->pdev->dev, "PHC enabled\n");
		pf->flags |= I40E_FLAG_PTP;


		regval = rd32(hw, I40E_PRTTSYN_CTL0);
		regval |= I40E_PRTTSYN_CTL0_TSYNENA_MASK;
		wr32(hw, I40E_PRTTSYN_CTL0, regval);
		regval = rd32(hw, I40E_PRTTSYN_CTL1);
		regval |= I40E_PRTTSYN_CTL1_TSYNENA_MASK;
		wr32(hw, I40E_PRTTSYN_CTL1, regval);


		i40e_ptp_set_increment(pf);


		i40e_ptp_set_timestamp_mode(pf, &pf->tstamp_config);


		ts = ktime_to_timespec64(ktime_get_real());
		i40e_ptp_settime(&pf->ptp_caps, &ts);
	}
}
