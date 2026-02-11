Note_informuseroflevelplus(userrec *u, u_long flag)
{
	char	msg[SERVERLEN], level[FLAGSHORTLEN];

	User_flags2str(flag,level);
	sprintf(msg,"You have been given the level +%s!",level);
	if(flag & USER_MASTER)
		sprintf(msg,"%s  You are a master now.  Be careful, +m means you can delete users, responses, locations, etc. even when not intended.  Have fun!",msg);
	else if(flag & USER_GREET)
		sprintf(msg,"%s  The bot will greet you when you join a channel.  You can set your own greetings with 'addgreet' and 'delgreet'.  Don't make the bot say stupid things, ok?  Think of something creative. :>  (See help on 'greets' for more info)",msg);
	else if(flag & USER_OP)
		sprintf(msg,"%s  You can get ops from the bot now with the command 'op', or by just sending your password with 'pass'.",msg);
	else if(flag & USER_VOICE)
		sprintf(msg,"%s  You can get the mode +v from the bot now with the command 'voice'.",msg);
	else if(flag & USER_NOTICES)
		sprintf(msg,"%s  You will now receive notices from the bot regarding bot status and activity.",msg);
	else if(flag & USER_TRUSTED)
		sprintf(msg,"%s  You can now make the bot do certain things now like leaving and joining a channel, kicking and banning, and other commands which require some degree of responsibility.",msg);
	else if(flag & USER_RESPONSE)
		sprintf(msg,"%s  You can add and delete responses from the bot!  Check out help on 'response' to see how one goes about doing this.  It's not as hard as it looks :>",msg);
	else if(flag & USER_31337)
		sprintf(msg,"%s  Welcome '1337 user :>",msg);
	else if(flag & USER_PROTECT)
		sprintf(msg,"%s  You will be protected by the bot from being banned.",msg);
	else if(flag & USER_FRIEND)
		sprintf(msg,"%s  You will be unbanned if ever you are banned on the channel.",msg);

	Note_sendnotice(u,msg);
}
