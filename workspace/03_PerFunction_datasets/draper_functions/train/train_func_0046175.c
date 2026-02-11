remove_unknown(aClient *cptr, char *sender)
{
	if (!IsRegistered(cptr) || IsClient(cptr))
		return;


	if (!IsServer(cptr))
		return;


	if ((index(sender, '.') && !index(sender, '@'))
		|| sid_valid(sender))
	    {
		sendto_flag(SCH_NOTICE, "Squitting unknown %s brought by %s.",
			    sender, get_client_name(cptr, FALSE));
		sendto_one(cptr, ":%s SQUIT %s :(Unknown from %s)",
			   me.name, sender, get_client_name(cptr, FALSE));
	    }
	else


		sendto_flag(SCH_NOTICE, "Dropping unknown %s brought by %s.",
			    sender, get_client_name(cptr, FALSE));
}
