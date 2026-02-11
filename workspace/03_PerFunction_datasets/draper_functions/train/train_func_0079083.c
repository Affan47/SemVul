exhalbtc_dbg_control(struct btc_coexist *btcoexist,
			  u8 code, u8 len, u8 *data)
{
	if (!halbtc_is_bt_coexist_available(btcoexist))
		return;
	btcoexist->statistics.cnt_dbg_ctrl++;
}
