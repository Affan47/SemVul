cmd_kick()
{
	chanrec	*chan;
	membrec	*m;
	char	nick[256], nicks[256], message[256];

	if(!cmdinfo.isparam)
	{
		say("Usage: kick [channel] <nick[,nick,...]> [message]");
		sayf(2,0,"Use this command to kick a user from the channel.  You can specify that multiple nicks be kicked in one blow, but make sure you don't put any spaces between the commas that separate the nicks.  If no channel is specified, user is kicked from all botted channels they are on.");
		return;
	}


	if(cmdinfo.tok1[0] == '#' || cmdinfo.tok1[0] == '&' || cmdinfo.tok1[0] == '+')
	{
		chan = Channel_channel(cmdinfo.tok1);
		if(chan == NULL)
		{
			sayf(0,0,"The channel \"%s\" is not known to me.",cmdinfo.tok1);
			return;
		}


		if(!Channel_ihaveops(chan))
		{
			say("Sorry, I don't have ops on channel %s.",chan->name);
			return;
		}

		if(!cmdinfo.istok2)
		{
			say("Usage: kick [channel] <nick[,nick,...]> [message]");
			sayf(2,0,"Use this command to kick a user from the channel.  You can specify that multiple nicks be kicked in one blow, but make sure you don't put any spaces between the commas that separate the nicks.  If no channel is specified, user is kicked from all botted channels they are on.");
			return;
		}

		if(!cmdinfo.istok3)
			strcpy(message,"Bye!");
		else
		{
			split(NULL,cmdinfo.param);
			split(NULL,cmdinfo.param);
			strcpy(message,cmdinfo.param);
		}


		splitc(nick,cmdinfo.tok2,',');
		while(nick[0])
		{
			m = Channel_member(chan,nick);
			if(m == NULL)
				say("No such nick \"%s\" on %s...",nick,chan->name);
			else if(!isequal(m->nick,Server->currentnick))
			{
				Server_write(PRIORITY_HIGH,"KICK %s %s :%s",chan->name,m->nick,message);
				say("Kicked %s from %s...",nick,chan->name);
			}

			splitc(nick,cmdinfo.tok2,',');
		}

		return;
	}


	if(!cmdinfo.istok2)
		strcpy(message,"Bye!");
	else
	{
		split(NULL,cmdinfo.param);
		strcpy(message,cmdinfo.param);
	}


	for(chan=Channel->channels; chan!=NULL; chan=chan->next)
	{
		if(!Channel_ihaveops(chan))
			continue;


		strcpy(nicks,cmdinfo.tok1);
		splitc(nick,nicks,',');
		while(nick[0])
		{
			m = Channel_member(chan,nick);
			if(m != NULL && !isequal(m->nick,Server->currentnick))
			{
				Server_write(PRIORITY_HIGH,"KICK %s %s :%s",chan->name,m->nick,message);
				say("Kicked %s from %s...",nick,chan->name);
			}

			splitc(nick,cmdinfo.tok2,',');
		}
	}
}
