myCdataBlock(void *ctx,const xmlChar *value,int len){
xmlParserCtxtPtr ctxt=(xmlParserCtxtPtr) ctx;
SaxReaderObject *reader=(SaxReaderObject *)ctxt->_private;

	if (ctxt->nodeNr>1){
		reader->cdataBlock(ctx,value,len);
	}
}
