handleDefProcessGroup( void* userData, uint32_t stream,
	uint32_t group, const char* name, uint32_t numberOfProcs,
	const uint32_t* procs, OTF_KeyValueList* kvlist ) {


  	uint32_t i;
	Control* c= (Control*) userData;


	if( c->records[OTF_DEFPROCESSGROUP_RECORD] ) {

		++c->num;
		if( c->num >= c->minNum && c->num <= c->maxNum && ! c->silent_mode ) {

			fprintf( c->outfile, "(#%llu) \tDefProcessGroup: stream %u, group %u, name \"%s\", procs ",
				(long long unsigned) c->num, stream, group, name );

			const char* sep= "";
			for( i= 0; i < numberOfProcs; ++i ) {
				fprintf( c->outfile, "%s%u", sep, procs[i] );
				sep= ", ";
			}

			printKeyValueList(c, kvlist);
		}
	}


	return OTF_RETURN_OK;
}
