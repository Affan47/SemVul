xmlTextReaderDoExpand(xmlTextReaderPtr reader) {
    int val;

    if ((reader == NULL) || (reader->node == NULL) || (reader->ctxt == NULL))
        return(-1);
    do {
        if (reader->ctxt->instate == XML_PARSER_EOF) return(1);

        if (xmlTextReaderGetSuccessor(reader->node) != NULL)
            return(1);
        if (reader->ctxt->nodeNr < reader->depth)
            return(1);
        if (reader->mode == XML_TEXTREADER_MODE_EOF)
            return(1);
        val = xmlTextReaderPushData(reader);
        if (val < 0)
            return(-1);
    } while(reader->mode != XML_TEXTREADER_MODE_EOF);
    return(1);
}
