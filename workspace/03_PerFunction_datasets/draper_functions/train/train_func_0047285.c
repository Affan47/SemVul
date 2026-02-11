UserUpdatePhrase( const uint16 phoneSeq[], const char wordSeq[] )
{
	HASH_ITEM *pItem;
	UserPhraseData data;
	int len;

	len = ueStrLen( (char *) wordSeq );
	pItem = HashFindEntry( phoneSeq, wordSeq );
	if ( ! pItem ) {
		if ( ! AlcUserPhraseSeq( &data, len, strlen( wordSeq ) ) ) {
			return USER_UPDATE_FAIL;
		}

		memcpy( data.phoneSeq, phoneSeq, len * sizeof( phoneSeq[ 0 ] ) );
		data.phoneSeq[ len ] = 0;
		strcpy( data.wordSeq, wordSeq );


		data.origfreq = LoadOriginalFreq( phoneSeq, wordSeq, len );
		data.maxfreq = LoadMaxFreq( phoneSeq, len );

		data.userfreq = data.origfreq;
		data.recentTime = chewing_lifetime;
		pItem = HashInsert( &data );
		HashModify( pItem );
		return USER_UPDATE_INSERT;
	}
	else {
		pItem->data.maxfreq = LoadMaxFreq( phoneSeq, len );
		pItem->data.userfreq = UpdateFreq(
			pItem->data.userfreq,
			pItem->data.maxfreq,
			pItem->data.origfreq,
			chewing_lifetime - pItem->data.recentTime );
		pItem->data.recentTime = chewing_lifetime;
		HashModify( pItem );
		return USER_UPDATE_MODIFY;
	}
}
