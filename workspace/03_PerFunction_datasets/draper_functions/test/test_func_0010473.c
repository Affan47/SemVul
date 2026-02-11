gfire_buddy_p2p_connected(gfire_buddy *p_buddy)
{
	if(!p_buddy)
		return;

	purple_debug_info("gfire", "P2P connected with buddy %s\n", gfire_buddy_get_name(p_buddy));

	p_buddy->hasP2P = GFP2P_YES;
	p_buddy->p2p_notify = FALSE;

	p_buddy->p2p_requested = FALSE;
	if(p_buddy->p2p_request_timeout)
	{
		purple_timeout_remove(p_buddy->p2p_request_timeout);
		p_buddy->p2p_request_timeout = 0;
	}
}
