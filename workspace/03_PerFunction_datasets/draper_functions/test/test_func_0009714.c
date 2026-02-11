handle_marker( void* fha, uint64_t time, uint32_t process,
                     uint32_t token, const char* text, OTF_KeyValueList* list ) {

    OTF_WStream* writer= (OTF_WStream*) fha;


    return (markerDispersionId == token ) ? OTF_RETURN_OK :
        OTF_WStream_writeMarkerKV( writer, time, process, token, text, list);

}
