carl9170_tx_bar_status(struct ar9170 *ar, struct sk_buff *skb,
	struct ieee80211_tx_info *tx_info)
{
	struct _carl9170_tx_superframe *super = (void *) skb->data;
	struct ieee80211_bar *bar = (void *) super->frame_data;


	if (unlikely(ieee80211_is_back_req(bar->frame_control)) &&
	   !(tx_info->flags & IEEE80211_TX_STAT_ACK)) {
		struct carl9170_bar_list_entry *entry;
		int queue = skb_get_queue_mapping(skb);

		rcu_read_lock();
		list_for_each_entry_rcu(entry, &ar->bar_list[queue], list) {
			if (entry->skb == skb) {
				spin_lock_bh(&ar->bar_list_lock[queue]);
				list_del_rcu(&entry->list);
				spin_unlock_bh(&ar->bar_list_lock[queue]);
				kfree_rcu(entry, head);
				goto out;
			}
		}

		WARN(1, "bar not found in %d - ra:%pM ta:%pM c:%x ssn:%x\n",
		       queue, bar->ra, bar->ta, bar->control,
			bar->start_seq_num);
out:
		rcu_read_unlock();
	}
}
