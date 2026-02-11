DoWord( char *buf )
{
	char keyBuf[ 128 ], phoneBuf[ 128 ];
	int phoneInx[ ZUIN_SIZE ];

	memset( phoneInx, 0, sizeof( phoneInx ) );
	sscanf( buf, "%s %s", keyBuf, word_data[ nWord ].word );
	if ( strlen( keyBuf ) > ZUIN_SIZE )
		return DO_WORD_ERROR;

	PhoneFromKey( phoneBuf, keyBuf, KB_DEFAULT, 1 );
	word_data[ nWord ].num[0] = UintFromPhone( phoneBuf );
	nWord++ ;
	return 0;
}
