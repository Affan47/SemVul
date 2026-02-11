ZuinPhoInput(ZuinData *pZuin, int key )
{
	switch ( pZuin->kbtype ) {
		case KB_HSU:
		case KB_DVORAK_HSU:
			return HsuPhoInput( pZuin,key );
			break;
		case KB_ET26:
			return ET26PhoInput( pZuin, key );
			break;
 		case KB_DACHEN_CP26:
 			return DACHENCP26PhoInput( pZuin, key );
 			break;
		case KB_HANYU_PINYIN:
			return PinYinInput( pZuin, key );
			break;
		default:
			return DefPhoInput( pZuin, key );
	}
	return ZUIN_ERROR;
}
