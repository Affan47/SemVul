handleDefFunction( void* firsthandlerarg, uint32_t streamid,
	uint32_t deftoken, const char* name, uint32_t group, uint32_t scltoken,
        OTF_KeyValueList* list ) {


	Control* control= (Control*) firsthandlerarg;

	if ( control->stats )
		control->stats->defFunction( deftoken, group );


    return OTF_CopyHandler_stream_DefFunction( control->def_wstream,
            0, deftoken, name, group, scltoken, list );
}
