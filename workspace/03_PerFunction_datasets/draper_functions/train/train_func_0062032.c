btc8723b2ant_wifi_rssi_state(struct btc_coexist *btcoexist,
				       u8 index, u8 level_num,
				       u8 rssi_thresh, u8 rssi_thresh1)
{
	s32 wifi_rssi = 0;
	u8 wifi_rssi_state = coex_sta->pre_wifi_rssi_state[index];

	btcoexist->btc_get(btcoexist, BTC_GET_S4_WIFI_RSSI, &wifi_rssi);

	if (level_num == 2) {
		if ((coex_sta->pre_wifi_rssi_state[index] ==
						BTC_RSSI_STATE_LOW) ||
		    (coex_sta->pre_wifi_rssi_state[index] ==
						BTC_RSSI_STATE_STAY_LOW)) {
			if (wifi_rssi >= rssi_thresh +
					 BTC_RSSI_COEX_THRESH_TOL_8723B_2ANT) {
				wifi_rssi_state = BTC_RSSI_STATE_HIGH;
				BTC_PRINT(BTC_MSG_ALGORITHM,
					  ALGO_WIFI_RSSI_STATE,
					  "[BTCoex], wifi RSSI state "
					  "switch to High\n");
			} else {
				wifi_rssi_state = BTC_RSSI_STATE_STAY_LOW;
				BTC_PRINT(BTC_MSG_ALGORITHM,
					  ALGO_WIFI_RSSI_STATE,
					  "[BTCoex], wifi RSSI state "
					  "stay at Low\n");
			}
		} else {
			if (wifi_rssi < rssi_thresh) {
				wifi_rssi_state = BTC_RSSI_STATE_LOW;
				BTC_PRINT(BTC_MSG_ALGORITHM,
					  ALGO_WIFI_RSSI_STATE,
					  "[BTCoex], wifi RSSI state "
					  "switch to Low\n");
			} else {
				wifi_rssi_state = BTC_RSSI_STATE_STAY_HIGH;
				BTC_PRINT(BTC_MSG_ALGORITHM,
					  ALGO_WIFI_RSSI_STATE,
					  "[BTCoex], wifi RSSI state "
					  "stay at High\n");
			}
		}
	} else if (level_num == 3) {
		if (rssi_thresh > rssi_thresh1) {
			BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_WIFI_RSSI_STATE,
				  "[BTCoex], wifi RSSI thresh error!!\n");
			return coex_sta->pre_wifi_rssi_state[index];
		}

		if ((coex_sta->pre_wifi_rssi_state[index] ==
						BTC_RSSI_STATE_LOW) ||
		    (coex_sta->pre_wifi_rssi_state[index] ==
						BTC_RSSI_STATE_STAY_LOW)) {
			if (wifi_rssi >= rssi_thresh +
					BTC_RSSI_COEX_THRESH_TOL_8723B_2ANT) {
				wifi_rssi_state = BTC_RSSI_STATE_MEDIUM;
				BTC_PRINT(BTC_MSG_ALGORITHM,
					  ALGO_WIFI_RSSI_STATE,
					  "[BTCoex], wifi RSSI state "
					  "switch to Medium\n");
			} else {
				wifi_rssi_state = BTC_RSSI_STATE_STAY_LOW;
				BTC_PRINT(BTC_MSG_ALGORITHM,
					  ALGO_WIFI_RSSI_STATE,
					  "[BTCoex], wifi RSSI state "
					  "stay at Low\n");
			}
		} else if ((coex_sta->pre_wifi_rssi_state[index] ==
						BTC_RSSI_STATE_MEDIUM) ||
			   (coex_sta->pre_wifi_rssi_state[index] ==
						BTC_RSSI_STATE_STAY_MEDIUM)) {
			if (wifi_rssi >= rssi_thresh1 +
					 BTC_RSSI_COEX_THRESH_TOL_8723B_2ANT) {
				wifi_rssi_state = BTC_RSSI_STATE_HIGH;
				BTC_PRINT(BTC_MSG_ALGORITHM,
					  ALGO_WIFI_RSSI_STATE,
					  "[BTCoex], wifi RSSI state "
					  "switch to High\n");
			} else if (wifi_rssi < rssi_thresh) {
				wifi_rssi_state = BTC_RSSI_STATE_LOW;
				BTC_PRINT(BTC_MSG_ALGORITHM,
					  ALGO_WIFI_RSSI_STATE,
					  "[BTCoex], wifi RSSI state "
					  "switch to Low\n");
			} else {
				wifi_rssi_state = BTC_RSSI_STATE_STAY_MEDIUM;
				BTC_PRINT(BTC_MSG_ALGORITHM,
					  ALGO_WIFI_RSSI_STATE,
					  "[BTCoex], wifi RSSI state "
					  "stay at Medium\n");
			}
		} else {
			if (wifi_rssi < rssi_thresh1) {
				wifi_rssi_state = BTC_RSSI_STATE_MEDIUM;
				BTC_PRINT(BTC_MSG_ALGORITHM,
					  ALGO_WIFI_RSSI_STATE,
					  "[BTCoex], wifi RSSI state "
					  "switch to Medium\n");
			} else {
				wifi_rssi_state = BTC_RSSI_STATE_STAY_HIGH;
				BTC_PRINT(BTC_MSG_ALGORITHM,
					  ALGO_WIFI_RSSI_STATE,
					  "[BTCoex], wifi RSSI state "
					  "stay at High\n");
			}
		}
	}

	coex_sta->pre_wifi_rssi_state[index] = wifi_rssi_state;

	return wifi_rssi_state;
}
