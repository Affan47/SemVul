got332()


{
	chanrec *chan;

	context;

	strcpy(Server->sbuf,Server->msg);
	str_element(Server->chname,Server->msg,2);
	split(NULL,Server->sbuf);
	split(NULL,Server->sbuf);
	fixcolon(Server->sbuf);

	context;

	chan = Channel_channel(Server->chname);
	if(chan == NULL)
	{
		Log_write(LOG_DEBUG,"*","Oops.  What am i doing on %s?",Server->chname);
		Server_write(PRIORITY_HIGH,"PART :%s",Server->chname);
		return;
	}
	else
		chanrec_settopic(chan,Server->sbuf);


	if(!(chan->modes & CHANMODE_GOTTOPIC))
	{
		chan->modes |= CHANMODE_GOTTOPIC;
		if(Channel_gotallchaninfo(chan))
			mode_pushchannelmodes(chan);
	}
}
