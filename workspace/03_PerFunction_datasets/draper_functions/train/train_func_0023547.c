rtl_op_sta_notify(struct ieee80211_hw *hw,
			      struct ieee80211_vif *vif,
			      enum sta_notify_cmd cmd,
			      struct ieee80211_sta *sta)
{
	switch (cmd) {
	case STA_NOTIFY_SLEEP:
		break;
	case STA_NOTIFY_AWAKE:
		break;
	default:
		break;
	}
}
