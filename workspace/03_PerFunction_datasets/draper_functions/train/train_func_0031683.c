cmd_act()
{
	chanrec	*chan;

	if(!cmdinfo.isparam)
	{
		say("Usage: act <channel> <message>");
		sayf(2,0,"Use this command to have the bot say an action to a channel.  Use 'say' to have the bot say a message normally.");
		return;
	}

	chan = Channel_channel(cmdinfo.tok1);
	if(chan == NULL)
	{
		sayf(0,0,"The channel \"%s\" is not known to me.",cmdinfo.tok1);
		return;
	}

	split(NULL,cmdinfo.param);
	Log_write(LOG_PUBLIC,chan->name,"<%s has ordered me to say the next message>",cmdinfo.user->acctname);
	sendaction(chan->name,cmdinfo.param);
}
