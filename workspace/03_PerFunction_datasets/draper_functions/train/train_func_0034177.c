exhalbtc_set_bt_patch_version(u16 bt_hci_version, u16 bt_patch_version)
{
	struct btc_coexist *btcoexist = &gl_bt_coexist;

	if (!halbtc_is_bt_coexist_available(btcoexist))
		return;

	btcoexist->bt_info.bt_real_fw_ver = bt_patch_version;
	btcoexist->bt_info.bt_hci_ver = bt_hci_version;
}
