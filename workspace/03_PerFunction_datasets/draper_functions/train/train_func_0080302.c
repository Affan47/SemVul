handlerDefKeyValue( void* firsthandlerarg, uint32_t stream, uint32_t key,
        OTF_Type type, const char* name, const char *description,
        OTF_KeyValueList* list ) {

    Control* control= (Control*) firsthandlerarg;

    if ( control->msgMatching ) {

        if ( control->maxKeyToken < key )
            control->maxKeyToken = key;

        if ( 0 == strcmp( name, OTFAUX_KEYVALUE_TUD_P2P_RECEIVED_TIME_NAME ) ) {
            control->recvTimeToken = key;
            return OTF_RETURN_OK;
        }
        if ( 0 == strcmp( name, OTFAUX_KEYVALUE_TUD_P2P_RECEIVED_SIZE_NAME ) ) {
            control->recvLengthToken = key;
            return OTF_RETURN_OK;
        }
        if ( 0 == strcmp( name, OTFAUX_KEYVALUE_TUD_P2P_RECEIVED_SCL_NAME ) ) {
            control->recvSclToken = key;
            return OTF_RETURN_OK;
        }
    }


    return OTF_CopyHandler_stream_DefKeyValue( control->def_wstream,
            0, key, type, name, description, list );
}
