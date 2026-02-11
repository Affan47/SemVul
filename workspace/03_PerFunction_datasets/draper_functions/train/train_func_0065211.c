me_rsfnc(struct Client *client_p, struct Client *source_p,
	int parc, const char *parv[])
{
	struct Client *target_p;
	struct Client *exist_p;
	time_t newts, curts;
	char note[NICKLEN + 10];

	if(!(source_p->flags & FLAGS_SERVICE))
		return 0;

	if((target_p = find_person(parv[1])) == NULL)
		return 0;

	if(!MyClient(target_p))
		return 0;

	if(!clean_nick(parv[2]))
		return 0;

	curts = atol(parv[4]);


	if(target_p->tsinfo != curts)
		return 0;

	if((exist_p = find_named_client(parv[2])))
	{
		char buf[BUFSIZE];


		if(target_p == exist_p)
			goto doit;

		if(MyClient(exist_p))
			sendto_one(exist_p, ":%s KILL %s :(Nickname regained by services)",
				me.name, exist_p->name);

		exist_p->flags |= FLAGS_KILLED;

		if(IsClient(exist_p))
		{
			kill_client_serv_butone(NULL, exist_p, "%s (Nickname regained by services)",
						me.name);
			sendto_realops_snomask(SNO_SKILL, L_ALL,
					"Nick collision due to services forced nick change on %s",
					parv[2]);
		}

		rb_snprintf(buf, sizeof(buf), "Killed (%s (Nickname regained by services))",
			me.name);
		exit_client(NULL, exist_p, &me, buf);
	}

doit:
	newts = atol(parv[3]);


	if(newts < (rb_current_time() - 900))
		newts = rb_current_time() - 900;

	target_p->tsinfo = newts;

	monitor_signoff(target_p);

	invalidate_bancache_user(target_p);

	sendto_realops_snomask(SNO_NCHANGE, L_ALL,
			"Nick change: From %s to %s [%s@%s]",
			target_p->name, parv[2], target_p->username,
			target_p->host);

	sendto_common_channels_local(target_p, NOCAPS, ":%s!%s@%s NICK :%s",
				target_p->name, target_p->username,
				target_p->host, parv[2]);

	add_history(target_p, 1);
	sendto_server(NULL, NULL, CAP_TS6, NOCAPS, ":%s NICK %s :%ld",
			use_id(target_p), parv[2], (long) target_p->tsinfo);

	del_from_client_hash(target_p->name, target_p);
	rb_strlcpy(target_p->name, parv[2], NICKLEN);
	add_to_client_hash(target_p->name, target_p);

	monitor_signon(target_p);

	del_all_accepts(target_p);

	rb_snprintf(note, NICKLEN + 10, "Nick: %s", target_p->name);
	rb_note(target_p->localClient->F, note);
	return 0;
}
