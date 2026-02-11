rfbVncAuthNone(rfbClientPtr cl)
{


    uint32_t authResult;


    if (cl->protocolMajorVersion==3 && cl->protocolMinorVersion > 7 && cl->protocolMinorVersion != 889) {
        rfbLog("rfbProcessClientSecurityType: returning securityResult for client rfb version >= 3.8\n");
        authResult = Swap32IfLE(rfbVncAuthOK);
        if (rfbWriteExact(cl, (char *)&authResult, 4) < 0) {
            rfbLogPerror("rfbAuthProcessClientMessage: write");
            rfbCloseClient(cl);
            return;
        }
    }
    cl->state = cl->protocolMinorVersion == 889 ? RFB_INITIALISATION_SHARED : RFB_INITIALISATION;
    if (cl->state == RFB_INITIALISATION_SHARED)


        rfbProcessClientMessage(cl);
    return;
}
