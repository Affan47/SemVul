cert_GetOCSPResponse(PLArenaPool *arena, const char *location,
                     const SECItem *encodedRequest)
{
    char *walkOutput = NULL;
    char *fullGetPath = NULL;
    size_t pathLength;
    PRInt32 urlEncodedBufLength;
    size_t base64size;
    char b64ReqBuf[max_get_request_size+1];
    size_t slashLengthIfNeeded = 0;
    size_t getURLLength;
    SECItem *item;

    if (!location || !*location) {
	return NULL;
    }

    pathLength = strlen(location);
    if (location[pathLength-1] != '/') {
	slashLengthIfNeeded = 1;
    }


    base64size = (((encodedRequest->len +2)/3) * 4);
    if (base64size > max_get_request_size) {
	return NULL;
    }
    memset(b64ReqBuf, 0, sizeof(b64ReqBuf));
    PL_Base64Encode((const char*)encodedRequest->data, encodedRequest->len,
		    b64ReqBuf);

    urlEncodedBufLength = ocsp_UrlEncodeBase64Buf(b64ReqBuf, NULL);
    getURLLength = pathLength + urlEncodedBufLength + slashLengthIfNeeded;


    if (arena) {
        fullGetPath = (char*)PORT_ArenaAlloc(arena, getURLLength);
    } else {
        fullGetPath = (char*)PORT_Alloc(getURLLength);
    }
    if (!fullGetPath) {
	return NULL;
    }

    strcpy(fullGetPath, location);
    walkOutput = fullGetPath + pathLength;

    if (walkOutput > fullGetPath && slashLengthIfNeeded) {
        strcpy(walkOutput, "/");
        ++walkOutput;
    }
    ocsp_UrlEncodeBase64Buf(b64ReqBuf, walkOutput);

    item = cert_FetchOCSPResponse(arena, fullGetPath, NULL);
    if (!arena) {
	PORT_Free(fullGetPath);
    }
    return item;
}
