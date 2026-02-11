DoHelloVerifyRequest(SSL* ssl, const byte* input,
                                    word32* inOutIdx)
    {
        ProtocolVersion pv;
        byte            cookieSz;

#ifdef CYASSL_CALLBACKS
        if (ssl->hsInfoOn) AddPacketName("HelloVerifyRequest",
                                         &ssl->handShakeInfo);
        if (ssl->toInfoOn) AddLateName("HelloVerifyRequest", &ssl->timeoutInfo);
#endif
        XMEMCPY(&pv, input + *inOutIdx, sizeof(pv));
        *inOutIdx += sizeof(pv);

        cookieSz = input[(*inOutIdx)++];

        if (cookieSz)
            *inOutIdx += cookieSz;

        ssl->options.serverState = SERVER_HELLOVERIFYREQUEST_COMPLETE;
        return 0;
    }
