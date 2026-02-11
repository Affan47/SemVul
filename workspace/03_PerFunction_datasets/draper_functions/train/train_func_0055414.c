handleDefFunctionGroup( void* userData, uint32_t stream,
	uint32_t funcGroup, const char* name, OTF_KeyValueList* kvlist ) {


	Control* c= (Control*) userData;


	if( c->records[OTF_DEFFUNCTIONGROUP_RECORD] ) {

		++c->num;
		if( c->num >= c->minNum && c->num <= c->maxNum && ! c->silent_mode ) {

			fprintf( c->outfile, "(#%llu) \tDefFunctionGroup: stream %u, group %u, name \"%s\"",
				(long long unsigned) c->num, stream, funcGroup, name );

			printKeyValueList(c, kvlist);
		}
	}


	return OTF_RETURN_OK;
}
