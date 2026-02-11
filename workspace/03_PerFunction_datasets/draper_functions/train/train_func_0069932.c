send_capabilities(struct Client *client_p, int cap_can_send)
{
	struct Capability *cap;
	char msgbuf[BUFSIZE];
	char *t;
	int tl;

	t = msgbuf;

	for(cap = captab; cap->name; ++cap)
	{
		if(cap->cap & cap_can_send)
		{
			tl = rb_sprintf(t, "%s ", cap->name);
			t += tl;
		}
	}

	t--;
	*t = '\0';

	sendto_one(client_p, "CAPAB :%s", msgbuf);
}
