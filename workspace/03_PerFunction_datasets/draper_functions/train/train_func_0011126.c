AlcUserPhraseSeq( UserPhraseData *pData, int phonelen, int wordlen )
{
	pData->phoneSeq = ALC( uint16, phonelen + 1 );
	pData->wordSeq = ALC( char, wordlen + 1 );
	return ( pData->phoneSeq && pData->wordSeq );
}
