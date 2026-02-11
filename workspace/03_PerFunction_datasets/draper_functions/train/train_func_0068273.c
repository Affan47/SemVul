do_naws(Sock *sock)
{
    unsigned int width, height, i;
    UCHAR octet[4];
    Sock *old_xsock;

    width = (emulation != EMUL_RAW && wrapflag && wrapsize) ?
	wrapsize : columns;
    height = winlines() + !visual;

    Sprintf(telbuf, "%c%c%c", TN_IAC, TN_SB, TN_NAWS);
    octet[0] = (width >> 8);
    octet[1] = (width & 0xFF);
    octet[2] = (height >> 8);
    octet[3] = (height & 0xFF);
    for (i = 0; i < 4; i++) {
        if (octet[i] == (UCHAR)TN_IAC) Stringadd(telbuf, TN_IAC);
        Stringadd(telbuf, octet[i]);
    }
    Sappendf(telbuf, "%c%c", TN_IAC, TN_SE);

    old_xsock = xsock;;
    xsock = sock;
    telnet_send(telbuf);
    xsock = old_xsock;
}
