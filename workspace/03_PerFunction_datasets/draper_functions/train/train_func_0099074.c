remove_unknown(struct Client *client_p, char *lsender, char *lbuffer)
{
	int slen = strlen(lsender);


	if((IsDigit(lsender[0]) && slen == 3) || (strchr(lsender, '.') != NULL))
	{
		sendto_realops_flags(UMODE_DEBUG, L_ALL,
				     "Unknown prefix (%s) from %s, Squitting %s",
				     lbuffer, client_p->name, lsender);

		sendto_one(client_p, ":%s SQUIT %s :(Unknown prefix (%s) from %s)",
			   get_id(&me, client_p), lsender, lbuffer, client_p->name);
	}
	else
		sendto_one(client_p, ":%s KILL %s :%s (Unknown Client)",
			   get_id(&me, client_p), lsender, me.name);
}
