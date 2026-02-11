rtcp_confirm(sockets *s)
{
	streams *sid;


	sid = get_sid(s->sid);
	if (sid)
	{
		LOGL(4, "Acknowledging stream %d via rtcp packet", s->sid);
		sid->rtime = s->rtime;
	}
	return 0;
}
