introduce_client(struct Client *client_p, struct Client *source_p)
{
	static char ubuf[12];

	if(MyClient(source_p))
		send_umode(source_p, source_p, 0, SEND_UMODES, ubuf);
	else
		send_umode(NULL, source_p, 0, SEND_UMODES, ubuf);

	if(!*ubuf)
	{
		ubuf[0] = '+';
		ubuf[1] = '\0';
	}


	if(has_id(source_p))
	{
		sendto_server(client_p, NULL, CAP_TS6, NOCAPS,
			      ":%s UID %s %d %ld %s %s %s %s %s :%s",
			      source_p->servptr->id, source_p->name,
			      source_p->hopcount + 1,
			      (long)source_p->tsinfo, ubuf,
			      source_p->username, source_p->host,
			      IsIPSpoof(source_p) ? "0" : source_p->sockhost,
			      source_p->id, source_p->info);

		sendto_server(client_p, NULL, NOCAPS, CAP_TS6,
			      "NICK %s %d %ld %s %s %s %s :%s",
			      source_p->name, source_p->hopcount + 1,
			      (long)source_p->tsinfo,
			      ubuf, source_p->username, source_p->host,
			      source_p->servptr->name, source_p->info);
	}
	else
		sendto_server(client_p, NULL, NOCAPS, NOCAPS,
			      "NICK %s %d %ld %s %s %s %s :%s",
			      source_p->name, source_p->hopcount + 1,
			      (long)source_p->tsinfo,
			      ubuf, source_p->username, source_p->host,
			      source_p->servptr->name, source_p->info);
}
