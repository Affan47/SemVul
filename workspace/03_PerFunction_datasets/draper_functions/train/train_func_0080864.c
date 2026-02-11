httpStateFree(int fd, void *data)
{
    HttpStateData *httpState = data;
#if DELAY_POOLS
    delayClearNoDelay(fd);
#endif
    if (httpState == NULL)
	return;
    if (httpState->body_buf) {
	requestAbortBody(httpState->orig_request);
	if (httpState->body_buf) {
	    memFree(httpState->body_buf, MEM_8K_BUF);
	    httpState->body_buf = NULL;
	}
    }
    storeUnlockObject(httpState->entry);
    if (!memBufIsNull(&httpState->reply_hdr)) {
	memBufClean(&httpState->reply_hdr);
    }
    requestUnlink(httpState->request);
    requestUnlink(httpState->orig_request);
    httpState->request = NULL;
    httpState->orig_request = NULL;
    stringClean(&httpState->chunkhdr);
    cbdataFree(httpState);
}
