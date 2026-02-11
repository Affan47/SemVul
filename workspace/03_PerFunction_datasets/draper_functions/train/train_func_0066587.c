_out_ep_mapping(struct ieee80211_hw *hw)
{
	int err = 0;
	bool bIsChipN, bwificfg = false;
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	struct rtl_usb_priv *usb_priv = rtl_usbpriv(hw);
	struct rtl_usb *rtlusb = rtl_usbdev(usb_priv);
	struct rtl_ep_map *ep_map = &(rtlusb->ep_map);

	bIsChipN = IS_NORMAL_CHIP(rtlhal->version);
	switch (rtlusb->out_ep_nums) {
	case 2:
		_TwoOutEpMapping(hw, bIsChipN, bwificfg, ep_map);
		break;
	case 3:

		if (!bIsChipN) {
			err  =  -EINVAL;
			goto err_out;
		}
		_ThreeOutEpMapping(hw, bIsChipN, ep_map);
		break;
	case 1:
		_OneOutEpMapping(hw, ep_map);
		break;
	default:
		err  =  -EINVAL;
		break;
	}
err_out:
	return err;

}
