AlcUserPhraseSeq( UserPhraseData *pData, int phonelen, int wordlen )
{
	pData->phoneSeq = ALC( uint16_t, phonelen + 1 );
	if ( !pData->phoneSeq )
		goto error;
	pData->wordSeq = ALC( char, wordlen + 1 );
	if ( !pData->wordSeq )
		goto error;

	return 1;

error:
	free( pData->phoneSeq );
	free( pData->wordSeq );
	return 0;
}
