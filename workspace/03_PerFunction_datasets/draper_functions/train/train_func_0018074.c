Response_checkforpublicflood(char *to)


{
	chanrec	*chan;
	time_t	now = time(NULL);
	int	i;

	if(to[0] == '#' || to[0] == '&' || to[0] == '+')
	{
		chan = Channel_channel(to);
		if(chan == NULL)
			return 0;

		if((chan->flags & CHAN_PUBLICFLOOD) || (chan->flags & CHAN_HUSH))
			return 0;


		chan->resp_boxes_pos = (chan->resp_boxes_pos + 1) % (Grufti->public_flood_num - 1);


		if((now - chan->resp_boxes[chan->resp_boxes_pos]) < Grufti->public_flood_interval)
		{

			chan->flags |= CHAN_PUBLICFLOOD;
			chan->start_public_flood = now;
			Log_write(LOG_PUBLIC,chan->name,"Public flood detected.  Forwarding all responses back to user.");
			sendprivmsg(chan->name,"I'm feeling bombarded!  Forwarding all responses back to user...");


			for(i=0; i<RESPRATE_NUM; i++)
				chan->resp_boxes[i] = 0L;
			return 0;
		}


		chan->resp_boxes[chan->resp_boxes_pos] = time(NULL);
		return 1;
	}

	return 0;
}
