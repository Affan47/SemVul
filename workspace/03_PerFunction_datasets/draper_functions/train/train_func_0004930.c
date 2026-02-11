net80211_accum_frags ( struct net80211_device *dev,
						int fcid, int nfrags, int size )
{
	struct net80211_frag_cache *frag = &dev->frags[fcid];
	int hdrsize = IEEE80211_TYP_FRAME_HEADER_LEN;
	int nsize = size - hdrsize * ( nfrags - 1 );
	int i;

	struct io_buffer *niob = alloc_iob ( nsize );
	struct ieee80211_frame *hdr;


	memcpy ( iob_put ( niob, hdrsize ), frag->iob[0]->data, hdrsize );


	for ( i = 0; i < nfrags; i++ ) {
		int len = iob_len ( frag->iob[i] ) - hdrsize;
		memcpy ( iob_put ( niob, len ),
			 frag->iob[i]->data + hdrsize, len );
	}


	hdr = niob->data;
	hdr->fc &= ~IEEE80211_FC_MORE_FRAG;

	return niob;
}
