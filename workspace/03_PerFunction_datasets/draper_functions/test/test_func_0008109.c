service_lookup(char *name)
{
	struct servent *serv_ent;

	if (!(serv_ent = getservbyname(name, "tcp")))
		return 0;
	else
		return htons(serv_ent->s_port);
}
