hci_switch_role(int dd, bdaddr_t *bdaddr, uint8_t role, int to)
{
	switch_role_cp cp;
	evt_role_change rp;
	struct hci_request rq;

	bacpy(&cp.bdaddr, bdaddr);
	cp.role   = role;
	rq.ogf    = OGF_LINK_POLICY;
	rq.ocf    = OCF_SWITCH_ROLE;
	rq.cparam = &cp;
	rq.clen   = SWITCH_ROLE_CP_SIZE;
	rq.rparam = &rp;
	rq.rlen   = EVT_ROLE_CHANGE_SIZE;
	rq.event  = EVT_ROLE_CHANGE;

	if (hci_send_req(dd, &rq, to) < 0)
		return -1;

	if (rp.status) {
		errno = EIO;
		return -1;
	}

	return 0;
}
