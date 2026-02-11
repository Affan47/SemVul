schedule_delivery(struct iax_event *e, unsigned int ts, int updatehistory)
{


#ifdef EXTREME_DEBUG
	DEBU(G "[%p] We are at %d, packet is for %d\n", e->session, calc_rxstamp(e->session), ts);
#endif


	if ( !iax_use_jitterbuffer ||
			(e->etype == IAX_EVENT_VIDEO &&
			 video_bypass_jitterbuffer) )
	{
		iax_sched_add(e, NULL, NULL, NULL, 0);
		return NULL;
	} else
	{
		int type = JB_TYPE_CONTROL;
		int len = 0;

		if(e->etype == IAX_EVENT_VOICE)
		{
			type = JB_TYPE_VOICE;

			len = get_sample_cnt(e) / 8;
		} else if(e->etype == IAX_EVENT_VIDEO)
		{
			type = JB_TYPE_VIDEO;
		} else if(e->etype == IAX_EVENT_CNG)
		{
			type = JB_TYPE_SILENCE;
		}


		ts = unwrap_timestamp(ts,e->session->last_ts);


		if(ts > e->session->last_ts)
		{
			e->session->last_ts = ts;
		}

		if(jb_put(e->session->jb, e, type, len, ts,
					calc_rxstamp(e->session)) == JB_DROP)
		{
			iax_event_free(e);
		}
	}

	return NULL;
}
