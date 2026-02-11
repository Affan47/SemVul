snd_emux_reset_port(struct snd_emux_port *port)
{
	int i;


	snd_emux_sounds_off_all(port);

	snd_midi_channel_set_clear(&port->chset);

#ifdef SNDRV_EMUX_USE_RAW_EFFECT
	snd_emux_clear_effect(port);
#endif


	port->ctrls[EMUX_MD_DEF_BANK] = 0;
	port->ctrls[EMUX_MD_DEF_DRUM] = 0;
	port->ctrls[EMUX_MD_REALTIME_PAN] = 1;

	for (i = 0; i < port->chset.max_channels; i++) {
		struct snd_midi_channel *chan = port->chset.channels + i;
		chan->drum_channel = ((port->drum_flags >> i) & 1) ? 1 : 0;
	}
}
