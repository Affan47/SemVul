ChapSendStatus(cstate, code)
    chap_state *cstate;
    int code;
{
    u_char *outp;
    int outlen, msglen;
    char msg[256];

    if (code == CHAP_SUCCESS)
	sprintf(msg, "Welcome to %s.", hostname);
    else
	sprintf(msg, "I don't like you.  Go 'way.");
    msglen = strlen(msg);

    outlen = CHAP_HEADERLEN + msglen;
    outp = outpacket_buf;

    MAKEHEADER(outp, PPP_CHAP);

    PUTCHAR(code, outp);
    PUTCHAR(cstate->chal_id, outp);
    PUTSHORT(outlen, outp);
    BCOPY(msg, outp, msglen);
    output(cstate->unit, outpacket_buf, outlen + PPP_HDRLEN);

    CHAPDEBUG((LOG_INFO, "ChapSendStatus: Sent code %d, id %d.", code,
	       cstate->chal_id));
}
