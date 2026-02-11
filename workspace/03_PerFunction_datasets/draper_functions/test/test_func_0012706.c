OTF_MapEntry_insertValue( OTF_MapEntry* mc, uint32_t value ) {


	unsigned int i;
	unsigned int j;
	unsigned int last;
	unsigned int middle;


	if ( mc->n >= mc->s ) {

		mc->s= ( mc->s > 0 ) ? ( 2* mc->s ) : 10;
		mc->values= (uint32_t*) realloc( mc->values,
			mc->s * sizeof(uint32_t) );
		if( NULL == mc->values ) {

			OTF_Error( "ERROR in function %s, file: %s, line: %i:\n "
					"no memory left.\n",
					__FUNCTION__, __FILE__, __LINE__ );

			return 0;
		}
	}


	if ( mc->n == 0 ) {

		mc->values[0] = value;
		mc->n++;
		return 1;
	}


	i = 0;
	last = mc->n-1;

	while ( i < last+1 )	{

		middle = ( i + last ) / 2;

		if( mc->values[middle] < value ) {

			i = middle + 1;

		} else if( mc->values[middle] > value ) {

			last = middle - 1;

		} else {


			return 0;
		}
	}


	for ( j= mc->n; j > i; j-- ) {

		mc->values[j]= mc->values[j-1];
	}

	mc->values[i]= value;

	mc->n++;

	return 1;
}
