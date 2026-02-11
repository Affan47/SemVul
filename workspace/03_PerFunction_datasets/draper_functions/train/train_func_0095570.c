dvorak_convert( int key )
{
	const char dkey[] = {
		'\'','\"',',','<','.','>','p','P','y','Y','f','F','g','G',
		'c','C','r','R','l','L','/','?','=','+','\\','|',
		'a','A','o','O','e','E','u','U','i','I','d','D','h','H',
		't','T','n','N','s','S','-','_',
		';',':','q','Q','j','J','k','K','x','X','b','B','m','M',
		'w','W','v','V','z','Z'};
	const char qkey[] = {
		'q','Q','w','W','e','E','r','R','t','T','y','Y','u','U',
		'i','I','o','O','p','P','[','{',']','}','\\','|',
		'a','A','s','S','d','D','f','F','g','G','h','H','j','J',
		'k','K','l','L',';',':','\'','\"',
		'z','Z','x','X','c','C','v','V','b','B','n','N','m','M',
		',','<','.','>','/','?'};
	size_t i;

	STATIC_ASSERT( ARRAY_SIZE( dkey ) == ARRAY_SIZE( qkey ), update_dkey_and_qkey );

	for ( i = 0; i < ARRAY_SIZE( dkey ); i++ ) {
		if ( key == qkey[ i ] ) {
			key = dkey[ i ];
			return key;
		}
	}
	return key;
}
