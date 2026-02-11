carl9170_ba_check(struct ar9170 *ar, void *data, unsigned int len)
{
	struct ieee80211_bar *bar = data;
	struct carl9170_bar_list_entry *entry;
	unsigned int queue;

	if (likely(!ieee80211_is_back(bar->frame_control)))
		return;

	if (len <= sizeof(*bar) + FCS_LEN)
		return;

	queue = TID_TO_WME_AC(((le16_to_cpu(bar->control) &
		IEEE80211_BAR_CTRL_TID_INFO_MASK) >>
		IEEE80211_BAR_CTRL_TID_INFO_SHIFT) & 7);

	rcu_read_lock();
	list_for_each_entry_rcu(entry, &ar->bar_list[queue], list) {
		struct sk_buff *entry_skb = entry->skb;
		struct _carl9170_tx_superframe *super = (void *)entry_skb->data;
		struct ieee80211_bar *entry_bar = (void *)super->frame_data;

#define TID_CHECK(a, b) (						\
	((a) & cpu_to_le16(IEEE80211_BAR_CTRL_TID_INFO_MASK)) ==	\
	((b) & cpu_to_le16(IEEE80211_BAR_CTRL_TID_INFO_MASK)))		\

		if (bar->start_seq_num == entry_bar->start_seq_num &&
		    TID_CHECK(bar->control, entry_bar->control) &&
		    ether_addr_equal_64bits(bar->ra, entry_bar->ta) &&
		    ether_addr_equal_64bits(bar->ta, entry_bar->ra)) {
			struct ieee80211_tx_info *tx_info;

			tx_info = IEEE80211_SKB_CB(entry_skb);
			tx_info->flags |= IEEE80211_TX_STAT_ACK;

			spin_lock_bh(&ar->bar_list_lock[queue]);
			list_del_rcu(&entry->list);
			spin_unlock_bh(&ar->bar_list_lock[queue]);
			kfree_rcu(entry, head);
			break;
		}
	}
	rcu_read_unlock();

#undef TID_CHECK
}
