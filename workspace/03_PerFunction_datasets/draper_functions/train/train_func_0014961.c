_clutter_timeline_do_tick (ClutterTimeline *timeline,
                           gint64           tick_time)
{
  ClutterTimelinePrivate *priv;

  priv = timeline->priv;


  if (!priv->is_playing)
    return;

  if (priv->waiting_first_tick)
    {
      priv->last_frame_time = tick_time;
      priv->msecs_delta = 0;
      priv->waiting_first_tick = FALSE;
      clutter_timeline_do_frame (timeline);
    }
  else
    {
      gint64 msecs;

      msecs = tick_time - priv->last_frame_time;


      if (msecs < 0)
        {
          priv->last_frame_time = tick_time;
          return;
        }

      if (msecs != 0)
	{

          priv->last_frame_time += msecs;
	  priv->msecs_delta = msecs;
	  clutter_timeline_do_frame (timeline);
	}
    }
}
