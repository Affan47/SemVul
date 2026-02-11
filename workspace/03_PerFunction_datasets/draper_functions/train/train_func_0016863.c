Channel_join(chanrec *chan)
{

	if(chan->flags & CHAN_LEAVE)
		return;

	if(chan->key && chan->key[0])
		Server_write(PRIORITY_HIGH,"JOIN %s %s",chan->name,chan->key);
	else
		Server_write(PRIORITY_HIGH,"JOIN %s",chan->name);
}
