HashFindPhonePhrase( const uint16 phoneSeq[], HASH_ITEM *pItemLast )
{
	HASH_ITEM *pNow = pItemLast ?
			pItemLast->next :
			hashtable[ HashFunc( phoneSeq ) ];

	for ( ; pNow; pNow = pNow->next )
		if ( PhoneSeqTheSame( pNow->data.phoneSeq, phoneSeq ) )
			return pNow;
	return NULL;
}
