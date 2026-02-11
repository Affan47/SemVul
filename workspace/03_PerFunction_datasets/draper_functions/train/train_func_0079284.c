OTF_MasterControl_insertMapEntry( OTF_MasterControl* mc,
		uint32_t argument, uint32_t pos ) {


	unsigned int i;


	if ( mc->n >= mc->s ) {

		mc->s= ( mc->s > 0 ) ? ( 2* mc->s ) : 10;
		mc->map= (OTF_MapEntry*) realloc( mc->map,
			mc->s * sizeof(OTF_MapEntry) );
		if( NULL == mc->map ) {

			OTF_Error( "ERROR in function %s, file: %s, line: %i:\n "
					"no memory left.\n",
					__FUNCTION__, __FILE__, __LINE__ );

			return NULL;
		}
	}


	for ( i= mc->n; i > pos; i-- ) {

		memcpy( &(mc->map[i]), &(mc->map[i-1]), sizeof(OTF_MapEntry) );
	}


	mc->map[pos].argument= argument;
	mc->map[pos].n= 0;
	mc->map[pos].s= 0;
	mc->map[pos].values= NULL;

	mc->n++;

	return &(mc->map[pos]);
}
