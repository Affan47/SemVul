handleDefVersion( void* userData, uint32_t stream, uint8_t major,
	uint8_t minor, uint8_t sub, const char* string ) {
	Control* c= (Control*) userData;


	if( c->records[OTF_DEFVERSION_RECORD] ) {

		++c->num;
		if( c->num >= c->minNum && c->num <= c->maxNum && ! c->silent_mode ) {

			fprintf( c->outfile, "(#%llu) \tDefVersion: stream %u, version: %u.%u.%u \"%s\"\n",
				(long long unsigned) c->num, stream, major, minor, sub, string );
		}
	}


	return OTF_RETURN_OK;
}
