ath_detect_bt_priority(struct ath9k_htc_priv *priv)
{
	struct ath_btcoex *btcoex = &priv->btcoex;
	struct ath_hw *ah = priv->ah;

	if (ath9k_hw_gpio_get(ah, ah->btcoex_hw.btpriority_gpio))
		btcoex->bt_priority_cnt++;

	if (time_after(jiffies, btcoex->bt_priority_time +
			msecs_to_jiffies(ATH_BT_PRIORITY_TIME_THRESHOLD))) {
		clear_bit(OP_BT_PRIORITY_DETECTED, &priv->op_flags);
		clear_bit(OP_BT_SCAN, &priv->op_flags);

		if (btcoex->bt_priority_cnt >= ATH_BT_CNT_SCAN_THRESHOLD) {
			ath_dbg(ath9k_hw_common(ah), BTCOEX,
				"BT scan detected\n");
			set_bit(OP_BT_PRIORITY_DETECTED, &priv->op_flags);
			set_bit(OP_BT_SCAN, &priv->op_flags);
		} else if (btcoex->bt_priority_cnt >= ATH_BT_CNT_THRESHOLD) {
			ath_dbg(ath9k_hw_common(ah), BTCOEX,
				"BT priority traffic detected\n");
			set_bit(OP_BT_PRIORITY_DETECTED, &priv->op_flags);
		}

		btcoex->bt_priority_cnt = 0;
		btcoex->bt_priority_time = jiffies;
	}
}
