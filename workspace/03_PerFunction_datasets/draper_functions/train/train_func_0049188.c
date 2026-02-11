stp_channel_add(stp_vars_t *v, unsigned channel, unsigned subchannel,
		double value)
{
  stpi_channel_group_t *cg = get_channel_group(v);
  stpi_channel_t *chan;
  stp_dprintf(STP_DBG_INK, v, "Add channel %d, %d, %f\n",
	      channel, subchannel, value);
  if (!cg)
    {
      cg = stp_zalloc(sizeof(stpi_channel_group_t));
      cg->black_channel = -1;
      cg->gloss_channel = -1;
      stp_allocate_component_data(v, "Channel", NULL, stpi_channel_free, cg);
      stp_dprintf(STP_DBG_INK, v, "*** Set up channel data ***\n");
    }
  if (channel >= cg->channel_count)
    {
      unsigned oc = cg->channel_count;
      cg->c = stp_realloc(cg->c, sizeof(stpi_channel_t) * (channel + 1));
      memset(cg->c + oc, 0, sizeof(stpi_channel_t) * (channel + 1 - oc));
      stp_dprintf(STP_DBG_INK, v, "*** Increment channel count from %d to %d\n",
		  oc, channel + 1);
      if (channel >= cg->channel_count)
	cg->channel_count = channel + 1;
    }
  chan = cg->c + channel;
  if (subchannel >= chan->subchannel_count)
    {
      unsigned oc = chan->subchannel_count;
      chan->sc =
	stp_realloc(chan->sc, sizeof(stpi_subchannel_t) * (subchannel + 1));
      (void) memset
	(chan->sc + oc, 0, sizeof(stpi_subchannel_t) * (subchannel + 1 - oc));
      chan->sc[subchannel].value = value;
      stp_dprintf(STP_DBG_INK, v,
		  "*** Increment subchannel count for %d from %d to %d\n",
		  channel, oc, subchannel + 1);
      if (subchannel >= chan->subchannel_count)
	chan->subchannel_count = subchannel + 1;
    }
  chan->sc[subchannel].value = value;
  chan->sc[subchannel].s_density = 65535;
  chan->sc[subchannel].cutoff = 0.75;
}
