writeOpenFileSnapshot( void*    userData,
                                uint64_t snapshotTime,
                                uint64_t eventTime,
                                uint64_t processId,
                                uint32_t fileId,
                                uint64_t handleId,
                                uint32_t scl,
                                void*    eventData ) {

    Control *control= ( Control* )userData;


    if ( eventData )
        OTF_KeyValueList_appendKeyValueList( control->kvlist,
                                             ( OTF_KeyValueList* )eventData );


    OTF_Writer_writeOpenFileSnapshotKV( control->writer,
                                        snapshotTime,
                                        eventTime,
                                        fileId,
                                        processId,
                                        handleId,
                                        scl,
                                        control->kvlist );

    return 1;
}
