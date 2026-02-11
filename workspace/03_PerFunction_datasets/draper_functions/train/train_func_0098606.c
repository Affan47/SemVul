StrAt ( const CurrentWord_t & Word, int iStart, int iLength, const char * szStr1 )
{
	if ( iStart < 0 || iStart >= Word.iLengthPadded )
		return false;

	char * szPos = (char *)Word.pWord + iStart;
	return !strncmp ( szPos, szStr1, iLength );
}
