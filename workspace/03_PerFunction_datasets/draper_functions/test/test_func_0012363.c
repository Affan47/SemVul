psendr(ppr, length, flags)

char			*ppr;
int4			length;
int4			flags;

{
	struct nmsg	nhead;

	LAM_ZERO_ME(nhead);
	nhead.nh_node = pq.pq_src_node;
	nhead.nh_event = pq.pq_src_event;
	nhead.nh_type = 0;
	nhead.nh_flags = flags | NREEL;
	nhead.nh_length = length;
	nhead.nh_msg = ppr;

	if (nsend(&nhead)) lampanic("kenyad (nsend)");
}
