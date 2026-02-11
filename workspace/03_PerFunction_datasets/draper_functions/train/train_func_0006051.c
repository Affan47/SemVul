exit_local_client(struct Client *client_p, struct Client *source_p, struct Client *from,
		  const char *comment)
{
	unsigned long on_for;
	char tbuf[26];

	exit_generic_client(client_p, source_p, from, comment);
	clear_monitor(source_p);

	s_assert(IsPerson(source_p));
	rb_dlinkDelete(&source_p->localClient->tnode, &lclient_list);
	rb_dlinkDelete(&source_p->lnode, &me.serv->users);

	if(IsOper(source_p))
		rb_dlinkFindDestroy(source_p, &local_oper_list);

	sendto_realops_snomask(SNO_CCONN, L_ALL,
			     "Client exiting: %s (%s@%s) [%s] [%s]",
			     source_p->name,
			     source_p->username, source_p->host, comment,
                             show_ip(NULL, source_p) ? source_p->sockhost : "255.255.255.255");

	sendto_realops_snomask(SNO_CCONNEXT, L_ALL,
			"CLIEXIT %s %s %s %s 0 %s",
			source_p->name, source_p->username, source_p->host,
                        show_ip(NULL, source_p) ? source_p->sockhost : "255.255.255.255",
			comment);

	on_for = rb_current_time() - source_p->localClient->firsttime;

	ilog(L_USER, "%s (%3lu:%02lu:%02lu): %s!%s@%s %s %d/%d",
		rb_ctime(rb_current_time(), tbuf, sizeof(tbuf)), on_for / 3600,
		(on_for % 3600) / 60, on_for % 60,
		source_p->name, source_p->username, source_p->host,
		source_p->sockhost,
		source_p->localClient->sendK, source_p->localClient->receiveK);

	sendto_one(source_p, "ERROR :Closing Link: %s (%s)", source_p->host, comment);
	close_connection(source_p);

	if((source_p->flags & FLAGS_KILLED) == 0)
	{
		sendto_server(client_p, NULL, CAP_TS6, NOCAPS,
			      ":%s QUIT :%s", use_id(source_p), comment);
	}

	SetDead(source_p);
	rb_dlinkAddAlloc(source_p, &dead_list);
	return(CLIENT_EXITED);
}
