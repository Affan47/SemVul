rtl_cam_mark_invalid(struct ieee80211_hw *hw, u8 uc_index)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);

	u32 ul_command;
	u32 ul_content;
	u32 ul_enc_algo = rtlpriv->cfg->maps[SEC_CAM_AES];

	switch (rtlpriv->sec.pairwise_enc_algorithm) {
	case WEP40_ENCRYPTION:
		ul_enc_algo = rtlpriv->cfg->maps[SEC_CAM_WEP40];
		break;
	case WEP104_ENCRYPTION:
		ul_enc_algo = rtlpriv->cfg->maps[SEC_CAM_WEP104];
		break;
	case TKIP_ENCRYPTION:
		ul_enc_algo = rtlpriv->cfg->maps[SEC_CAM_TKIP];
		break;
	case AESCCMP_ENCRYPTION:
		ul_enc_algo = rtlpriv->cfg->maps[SEC_CAM_AES];
		break;
	default:
		ul_enc_algo = rtlpriv->cfg->maps[SEC_CAM_AES];
	}

	ul_content = (uc_index & 3) | ((u16) (ul_enc_algo) << 2);

	ul_content |= BIT(15);
	ul_command = CAM_CONTENT_COUNT * uc_index;
	ul_command = ul_command | BIT(31) | BIT(16);

	rtl_write_dword(rtlpriv, rtlpriv->cfg->maps[WCAMI], ul_content);
	rtl_write_dword(rtlpriv, rtlpriv->cfg->maps[RWCAM], ul_command);

	RT_TRACE(rtlpriv, COMP_SEC, DBG_DMESG,
		 "rtl_cam_mark_invalid(): WRITE A4: %x\n", ul_content);
	RT_TRACE(rtlpriv, COMP_SEC, DBG_DMESG,
		 "rtl_cam_mark_invalid(): WRITE A0: %x\n", ul_command);
}
