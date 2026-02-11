HashFindEntry( const uint16 phoneSeq[], const char wordSeq[] )
{
	HASH_ITEM *pItem;
	int hashvalue;

	hashvalue = HashFunc( phoneSeq );

	for ( pItem = hashtable[ hashvalue ]; pItem ; pItem = pItem->next ) {
		if (
			! strcmp( pItem->data.wordSeq, wordSeq ) &&
			PhoneSeqTheSame( pItem->data.phoneSeq, phoneSeq ) ) {
			return pItem;
		}
	}
	return NULL;
}
