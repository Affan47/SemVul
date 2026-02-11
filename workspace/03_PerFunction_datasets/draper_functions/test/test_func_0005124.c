Netchan_NeedReliable (netchan_t *chan)
{


	if ((chan->incoming_acknowledged > chan->last_reliable_sequence
	&& chan->incoming_reliable_acknowledged != chan->reliable_sequence)
		||

	(!chan->reliable_length && chan->message.cursize))
	{
		return true;
	}

	return false;
}
