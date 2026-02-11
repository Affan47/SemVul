me_xline(struct Client *client_p, struct Client *source_p, int parc, const char *parv[])
{

	if(!IsPerson(source_p))
		return 0;

	handle_remote_xline(source_p, atoi(parv[1]), parv[2], parv[4]);
	return 0;
}
