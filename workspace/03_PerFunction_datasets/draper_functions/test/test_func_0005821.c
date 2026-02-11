get_true_pan(DUMB_IT_SIGDATA *sigdata, IT_CHANNEL *channel)
{
	channel->truepan = channel->pan << IT_ENVELOPE_SHIFT;

	if (!IT_IS_SURROUND_SHIFTED(channel->truepan) && (sigdata->flags & IT_USE_INSTRUMENTS)) {
		IT_INSTRUMENT *instrument = &sigdata->instrument[channel->instrument-1];
		int truepan = channel->truepan;
		truepan += (channel->note - instrument->pp_centre) * instrument->pp_separation << (IT_ENVELOPE_SHIFT - 3);
		channel->truepan = (unsigned short)MID(0, truepan, 64 << IT_ENVELOPE_SHIFT);
	}
}
