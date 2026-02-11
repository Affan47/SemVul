LoadChar( char *buf, int buf_len, uint16 phoneSeq[], int nPhoneSeq )
{
	int i;
	Word word;

	memset(buf, 0, buf_len);
	for ( i = 0; i < nPhoneSeq; i++ ) {
		GetCharFirst( &word, phoneSeq[ i ] );
		strncat(buf, word.word, buf_len);
	}
	buf[ buf_len - 1 ] = '\0';
}
