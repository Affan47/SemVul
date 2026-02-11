sftp_recv(void)
{
    struct sftp_packet *pkt;
    char x[4];
    unsigned char uc;

    if (!sftp_recvdata(x, 4)) {
	fxp_internal_error("sftp_recvdata failed, could not receive packet length");
	return NULL;
    }

    pkt = snew(struct sftp_packet);
    pkt->savedpos = 0;
    pkt->length = pkt->maxlen = GET_32BIT(x);
    pkt->data = snewn(pkt->length, char);

    if (!sftp_recvdata(pkt->data, pkt->length)) {
	fxp_internal_error("sftp_recvdata failed, could not receive packet contents");
	sftp_pkt_free(pkt);
	return NULL;
    }

    if (!sftp_pkt_getbyte(pkt, &uc)) {
	fxp_internal_error("sftp_pkt_getbyte failed");
	sftp_pkt_free(pkt);
	return NULL;
    } else {
	pkt->type = uc;
    }

    return pkt;
}
