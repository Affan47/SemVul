mclient_test(struct Client *client_p, struct Client *source_p, int parc, const char *parv[])
{
	if(parc < 2)
	{
		sendto_one_notice(source_p, ":You are a normal user, and sent no parameters");
	}
	else
	{
		sendto_one_notice(source_p, ":You are a normal user, and send parameters: %s", parv[1]);
	}


	call_hook(doing_example_hook, NULL);

	return 0;
}
