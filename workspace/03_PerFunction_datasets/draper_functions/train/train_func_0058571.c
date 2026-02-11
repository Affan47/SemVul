xmlSecBufferAppend(xmlSecBufferPtr buf, const xmlSecByte* data, xmlSecSize size) {
    int ret;

    xmlSecAssert2(buf != NULL, -1);

    if(size > 0) {
	xmlSecAssert2(data != NULL, -1);

        ret = xmlSecBufferSetMaxSize(buf, buf->size + size);
	if(ret < 0) {
	    xmlSecError(XMLSEC_ERRORS_HERE,
			NULL,
			"xmlSecBufferSetMaxSize",
			XMLSEC_ERRORS_R_XMLSEC_FAILED,
			"size=%d", buf->size + size);
	    return(-1);
	}

	memcpy(buf->data + buf->size, data, size);
	buf->size += size;
    }

    return(0);
}
