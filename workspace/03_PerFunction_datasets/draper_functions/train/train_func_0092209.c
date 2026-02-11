xmlSecBufferRemoveHead(xmlSecBufferPtr buf, xmlSecSize size) {
    xmlSecAssert2(buf != NULL, -1);

    if(size < buf->size) {
	xmlSecAssert2(buf->data != NULL, -1);

	buf->size -= size;
	memmove(buf->data, buf->data + size, buf->size);
    } else {
	buf->size = 0;
    }
    if(buf->size < buf->maxSize) {
	xmlSecAssert2(buf->data != NULL, -1);
	memset(buf->data + buf->size, 0, buf->maxSize - buf->size);
    }
    return(0);
}
