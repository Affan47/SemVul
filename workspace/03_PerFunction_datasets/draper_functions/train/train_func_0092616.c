rfbVncAuthSendChallenge(rfbClientPtr cl)
{


    rfbRandomBytes(cl->authChallenge);
    if (rfbWriteExact(cl, (char *)cl->authChallenge, CHALLENGESIZE) < 0) {
        rfbLogPerror("rfbAuthNewClient: write");
        rfbCloseClient(cl);
        return;
    }


    cl->state = RFB_AUTHENTICATION;
}
