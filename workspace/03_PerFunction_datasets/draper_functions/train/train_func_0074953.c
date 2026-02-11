disconn_complete(struct vhci_conn *conn)
{
	uint8_t buf[HCI_MAX_FRAME_SIZE], *ptr = buf;
	evt_disconn_complete *dc;
	hci_event_hdr *he;


	*ptr++ = HCI_EVENT_PKT;


	he = (void *) ptr; ptr += HCI_EVENT_HDR_SIZE;

	he->evt  = EVT_DISCONN_COMPLETE;
	he->plen = EVT_DISCONN_COMPLETE_SIZE;

	dc = (void *) ptr; ptr += EVT_DISCONN_COMPLETE_SIZE;

	dc->status = 0x00;
	dc->handle = htobs(conn->handle);
	dc->reason = 0x00;

	write_snoop(vdev.dd, HCI_EVENT_PKT, 1, buf, ptr - buf);

	if (write(vdev.dev_fd, buf, ptr - buf) < 0)
		syslog(LOG_ERR, "Can't send event: %s (%d)",
						strerror(errno), errno);

	vdev.acl_cnt = 0;
}
