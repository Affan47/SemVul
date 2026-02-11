distribute_hostchange(struct Client *client_p, char *newhost)
{
	if (newhost != client_p->orighost)
		sendto_one_numeric(client_p, RPL_HOSTHIDDEN, "%s :is now your hidden host",
			newhost);
	else
		sendto_one_numeric(client_p, RPL_HOSTHIDDEN, "%s :hostname reset",
			newhost);

	sendto_server(NULL, NULL,
		CAP_EUID | CAP_TS6, NOCAPS, ":%s CHGHOST %s :%s",
		use_id(&me), use_id(client_p), newhost);
	sendto_server(NULL, NULL,
		CAP_TS6, CAP_EUID, ":%s ENCAP * CHGHOST %s :%s",
		use_id(&me), use_id(client_p), newhost);

	change_nick_user_host(client_p, client_p->name, client_p->username, newhost, 0, "Changing host");

	if (newhost != client_p->orighost)
		SetDynSpoof(client_p);
	else
		ClearDynSpoof(client_p);
}
