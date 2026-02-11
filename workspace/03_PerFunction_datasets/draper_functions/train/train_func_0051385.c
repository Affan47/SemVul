mc_nick(struct Client *client_p, struct Client *source_p, int parc, const char *parv[])
{
	struct Client *target_p;
	time_t newts = 0;


	if(!clean_nick(parv[1], 0))
	{
		bad_nickname(client_p, parv[1]);
		return 0;
	}

	newts = atol(parv[2]);
	target_p = find_named_client(parv[1]);


	if(target_p == NULL)
	{
		change_remote_nick(client_p, source_p, newts, parv[1], 1);
	}
	else if(IsUnknown(target_p))
	{
		exit_client(NULL, target_p, &me, "Overridden");
		change_remote_nick(client_p, source_p, newts, parv[1], 1);
	}
	else if(target_p == source_p)
	{

		if(strcmp(target_p->name, parv[1]))
			change_remote_nick(client_p, source_p, newts, parv[1], 1);
	}

	else
		perform_nickchange_collides(source_p, client_p, target_p,
					    parc, parv, newts, parv[1]);

	return 0;
}
