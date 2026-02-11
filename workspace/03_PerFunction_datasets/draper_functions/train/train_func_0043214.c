xfer_upload_gotpkt(struct fxp_xfer *xfer, struct sftp_packet *pktin)
{
    struct sftp_request *rreq;
    struct req *rr, *prev, *next;
    int ret;

    rreq = sftp_find_request(pktin);
    rr = (struct req *)fxp_get_userdata(rreq);
    if (!rr)
	return 0;
    ret = fxp_write_recv(pktin, rreq);
#ifdef DEBUG_UPLOAD
    printf("write request %p has returned [%d]\n", rr, ret);
#endif


    prev = rr->prev;
    next = rr->next;
    if (prev)
	prev->next = next;
    else
	xfer->head = next;
    if (next)
	next->prev = prev;
    else
	xfer->tail = prev;
    xfer->req_totalsize -= rr->len;
    xfer->sent_interval += rr->len;
    if (fz_timer_check(&xfer->send_timer)) {

	fzprintf(sftpRead, "%d", xfer->sent_interval);
	xfer->sent_interval = 0;
    }
    sfree(rr);

    if (!ret)
	return -1;

    return 1;
}
