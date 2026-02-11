psndo_(int4 *pnode, int4* pevent, int4* ptype, int4* ierror)
{
	struct nmsg	nhead;

	nhead.nh_node = *pnode;
	nhead.nh_event = *pevent;
	nhead.nh_type = *ptype;

	if (psendopen(&nhead)) {
		*ierror = errno;
	} else {
		*ierror = 0;
	}
}
