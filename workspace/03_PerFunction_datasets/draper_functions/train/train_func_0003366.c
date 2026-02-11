sftp_pkt_getstring(struct sftp_packet *pkt,
			      char **p, int *length)
{
    *p = NULL;
    if (pkt->length - pkt->savedpos < 4)
	return 0;
    *length = GET_32BIT(pkt->data + pkt->savedpos);
    pkt->savedpos += 4;
    if ((int)(pkt->length - pkt->savedpos) < *length || *length < 0) {
	*length = 0;
	return 0;
    }
    *p = pkt->data + pkt->savedpos;
    pkt->savedpos += *length;
    return 1;
}
