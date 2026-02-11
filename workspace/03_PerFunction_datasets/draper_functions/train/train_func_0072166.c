net80211_handle_assoc_reply ( struct net80211_device *dev,
					  struct io_buffer *iob )
{
	struct ieee80211_frame *hdr = iob->data;
	struct ieee80211_assoc_resp *assoc =
		( struct ieee80211_assoc_resp * ) hdr->data;

	net80211_process_capab ( dev, assoc->capability );
	net80211_process_ie ( dev, assoc->info_element, iob->tail );

	if ( assoc->status != IEEE80211_STATUS_SUCCESS ) {
		DBGC ( dev, "802.11 %p association failed: status %d\n",
		       dev, assoc->status );
		net80211_set_state ( dev, NET80211_WAITING, 0,
				     assoc->status );
		return;
	}


	memcpy ( dev->bssid, hdr->addr3, ETH_ALEN );
	dev->aid = assoc->aid;

	net80211_set_state ( dev, NET80211_WAITING, NET80211_ASSOCIATED,
			     IEEE80211_STATUS_SUCCESS );
}
