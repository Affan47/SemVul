start_ep0(struct m66592_ep *ep, struct m66592_request *req)
{
	u16 ctsq;

	ctsq = m66592_read(ep->m66592, M66592_INTSTS0) & M66592_CTSQ;

	switch (ctsq) {
	case M66592_CS_RDDS:
		start_ep0_write(ep, req);
		break;
	case M66592_CS_WRDS:
		start_packet_read(ep, req);
		break;

	case M66592_CS_WRND:
		control_end(ep->m66592, 0);
		break;
	default:
		pr_err("start_ep0: unexpect ctsq(%x)\n", ctsq);
		break;
	}
}
