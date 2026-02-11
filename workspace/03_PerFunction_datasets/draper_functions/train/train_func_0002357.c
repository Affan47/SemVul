net80211_rx_frag ( struct net80211_device *dev,
			       struct io_buffer *iob, int signal )
{
	struct ieee80211_frame *hdr = iob->data;
	int fragnr = IEEE80211_FRAG ( hdr->seq );

	if ( fragnr == 0 && ( hdr->fc & IEEE80211_FC_MORE_FRAG ) ) {

		int i, newest = -1;
		u32 curr_ticks = currticks(), newest_ticks = 0;
		u32 timeout = ticks_per_sec() * NET80211_FRAG_TIMEOUT;

		for ( i = 0; i < NET80211_NR_CONCURRENT_FRAGS; i++ ) {
			if ( dev->frags[i].in_use == 0 )
				break;

			if ( dev->frags[i].start_ticks + timeout >=
			     curr_ticks ) {
				net80211_free_frags ( dev, i );
				break;
			}

			if ( dev->frags[i].start_ticks > newest_ticks ) {
				newest = i;
				newest_ticks = dev->frags[i].start_ticks;
			}
		}


		if ( i == NET80211_NR_CONCURRENT_FRAGS ) {
			i = newest;
			net80211_free_frags ( dev, i );
		}

		dev->frags[i].in_use = 1;
		dev->frags[i].seqnr = IEEE80211_SEQNR ( hdr->seq );
		dev->frags[i].start_ticks = currticks();
		dev->frags[i].iob[0] = iob;
		return;
	} else {
		int i;
		for ( i = 0; i < NET80211_NR_CONCURRENT_FRAGS; i++ ) {
			if ( dev->frags[i].in_use && dev->frags[i].seqnr ==
			     IEEE80211_SEQNR ( hdr->seq ) )
				break;
		}
		if ( i == NET80211_NR_CONCURRENT_FRAGS ) {

			DBGC ( dev, "802.11 %p dropped fragment fc=%04x "
			       "seq=%04x\n", dev, hdr->fc, hdr->seq );
			free_iob ( iob );
			return;
		}

		dev->frags[i].iob[fragnr] = iob;

		if ( ! ( hdr->fc & IEEE80211_FC_MORE_FRAG ) ) {
			int j, size = 0;
			for ( j = 0; j < fragnr; j++ ) {
				size += iob_len ( dev->frags[i].iob[j] );
				if ( dev->frags[i].iob[j] == NULL )
					break;
			}
			if ( j == fragnr ) {

				struct io_buffer *niob =
				    net80211_accum_frags ( dev, i, fragnr,
							   size );
				net80211_free_frags ( dev, i );
				net80211_rx ( dev, niob, signal, 0 );
			} else {
				DBGC ( dev, "802.11 %p dropping fragmented "
				       "packet due to out-of-order arrival, "
				       "fc=%04x seq=%04x\n", dev, hdr->fc,
				       hdr->seq );
				net80211_free_frags ( dev, i );
			}
		}
	}
}
