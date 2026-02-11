got368()


{
	chanrec	*chan;

	str_element(Server->chname,Server->msg,2);
	chan = Channel_channel(Server->chname);
	if(chan == NULL)
		return;

	if(!(chan->modes & CHANMODE_GOTBANS))
	{
		chan->modes |= CHANMODE_GOTBANS;
		if(Channel_gotallchaninfo(chan))
			mode_pushchannelmodes(chan);
	}
}
