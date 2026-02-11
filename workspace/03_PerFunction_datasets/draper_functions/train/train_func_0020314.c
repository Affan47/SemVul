prism2_frag_cache_get(local_info_t *local, struct ieee80211_hdr *hdr)
{
	struct sk_buff *skb = NULL;
	u16 sc;
	unsigned int frag, seq;
	struct prism2_frag_entry *entry;

	sc = le16_to_cpu(hdr->seq_ctrl);
	frag = sc & IEEE80211_SCTL_FRAG;
	seq = (sc & IEEE80211_SCTL_SEQ) >> 4;

	if (frag == 0) {

		skb = dev_alloc_skb(local->dev->mtu +
				    sizeof(struct ieee80211_hdr) +
				    8  +
				    2  +
				    8  + ETH_ALEN );
		if (skb == NULL)
			return NULL;

		entry = &local->frag_cache[local->frag_next_idx];
		local->frag_next_idx++;
		if (local->frag_next_idx >= PRISM2_FRAG_CACHE_LEN)
			local->frag_next_idx = 0;

		if (entry->skb != NULL)
			dev_kfree_skb(entry->skb);

		entry->first_frag_time = jiffies;
		entry->seq = seq;
		entry->last_frag = frag;
		entry->skb = skb;
		memcpy(entry->src_addr, hdr->addr2, ETH_ALEN);
		memcpy(entry->dst_addr, hdr->addr1, ETH_ALEN);
	} else {


		entry = prism2_frag_cache_find(local, seq, frag, hdr->addr2,
					       hdr->addr1);
		if (entry != NULL) {
			entry->last_frag = frag;
			skb = entry->skb;
		}
	}

	return skb;
}
