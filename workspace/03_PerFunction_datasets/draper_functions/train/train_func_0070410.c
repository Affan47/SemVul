getBuffer(int32_t& len, UErrorCode& status){
    if (U_FAILURE(status)) {
        return NULL;
    }
    len = ucbuf_size(ucharBuf);
    buffer =  (UChar*) uprv_malloc(U_SIZEOF_UCHAR * (len+1));
    u_strncpy(buffer,ucbuf_getBuffer(ucharBuf,&bufferLen,&status),len);
    buffer[len]=0;
    len = bufferLen;
    return buffer;
}
