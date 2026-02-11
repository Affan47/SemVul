load_session( char *filename )
{
    int rValue;
    xmlDocPtr  doc;
    xmlNodePtr node;
    xmlChar*   value;

    doc   = NULL;
    node  = NULL;
    value = NULL;
    rValue = SESSION_LOADED_OK;

    doc = xmlReadFile( filename, NULL, 0 );
    if( NULL == doc ) {
        rValue = SESSION_ERR_FILEREAD;
        goto done;
    }


    node = xmlDocGetRootElement( doc );
    if( xmlStrcmp(node->name, (const xmlChar *) "gopchop") ) {
        rValue = SESSION_ERR_NOT_GOPCHOP_FILE;
        goto done;
    }


    node = node->xmlChildrenNode;


    while( NULL != node ) {
        if( 0 == xmlStrcmp(node->name, (const xmlChar *)"filename") ) {
            value = xmlNodeListGetString( doc, node->xmlChildrenNode, 1 );
            open_file( (char*) value);
            xmlFree(value);
            value = NULL;
        }

        if( 0 == xmlStrcmp(node->name, (const xmlChar *)"clips") ) {
            handle_clips( node->xmlChildrenNode );
        }

        node = node->next;
    }


done:
    if( NULL != doc   ) xmlFreeDoc( doc );
    if( NULL != value ) xmlFree( value );

    xmlCleanupParser();
    xmlMemoryDump();
    return rValue;
}
