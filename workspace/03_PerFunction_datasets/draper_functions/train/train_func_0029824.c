lmtp_writeCB (EndPoint e UNUSED, IoStatus i UNUSED, Buffer *b,
	void *d)
{
    connection_t *cxn = (connection_t *) d;
    Buffer *readBuffers;

    clearTimer (cxn->lmtp_writeBlockedTimerId) ;


    freeBufferArray (b);
    if (cxn->lmtp_tofree_str!=NULL)
    {
	free(cxn->lmtp_tofree_str);
	cxn->lmtp_tofree_str=NULL;
    }


    readBuffers = makeBufferArray (bufferTakeRef (cxn->lmtp_rBuffer), NULL) ;
    prepareRead(cxn->lmtp_endpoint, readBuffers, lmtp_readCB, cxn, 5);


    clearTimer (cxn->lmtp_readBlockedTimerId) ;

    if (cxn->lmtp_readTimeout > 0)
	cxn->lmtp_readBlockedTimerId = prepareSleep (lmtp_readTimeoutCbk,
						     cxn->lmtp_readTimeout, cxn) ;


    switch (cxn->lmtp_state)
	{

	case LMTP_WRITING_LHLO:
	    cxn->lmtp_state = LMTP_READING_LHLO;
	    break;

	case LMTP_WRITING_STARTAUTH:
	case LMTP_WRITING_STEPAUTH:

	    cxn->lmtp_state = LMTP_READING_STEPAUTH;

	    break;

	case LMTP_WRITING_UPTODATA:

	    cxn->lmtp_state = LMTP_READING_RSET;
	    break;

	case LMTP_WRITING_CONTENTS:


	    cxn->lmtp_state = LMTP_READING_CONTENTS;

	    break;

	case LMTP_WRITING_NOOP:
	    cxn->lmtp_state = LMTP_READING_NOOP;
	    break;

	case LMTP_WRITING_QUIT:
	    cxn->lmtp_state = LMTP_READING_QUIT;
	    break;

	default:

	    d_printf(0,"%s:%d:LMTP Unknown state. Internal error\n",
		     hostPeerName (cxn->myHost), cxn->ident) ;

	    break;
	}
}
