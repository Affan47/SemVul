play_instrument(gint16 *dest, channel_t *channel, int count)
{
	int index = 0;
	int vol = hw_channels[channel->hw_channel].volume;
	instrument_t *instrument = bank.instruments[channel->instrument];

	while (1) {

		frac_t lin_avail;
		int seg_end, rem, i, amount;
		sbyte *samples;

		if (channel->looping) {
			samples = instrument->loop;
			seg_end = instrument->loop_size;
		}
		else {
			samples = instrument->samples;
			seg_end = instrument->size;
		}

		lin_avail = int_to_frac(seg_end) - channel->offset;

		rem = count - index;


		amount = lin_avail / channel->rate;

		if (lin_avail % channel->rate)
			amount++;

		if (amount > rem)
			amount = rem;


		if ((channel->envelope_samples != -1) && (amount > channel->envelope_samples))
			amount = channel->envelope_samples;

		for (i = 0; i < amount; i++) {
			dest[index++] = interpolate(samples, channel->offset) * channel->velocity / 64 * channel->note_velocity * vol / (127 * 127);
			channel->offset += channel->rate;
		}

		if (channel->envelope_samples != -1)
			channel->envelope_samples -= amount;

		if (channel->envelope_samples == 0) {
			envelope_t *envelope;
			int delta, target, velocity;

			if (channel->decay)
				envelope = &env_decay;
			else
				envelope = &instrument->envelope[channel->envelope];

			delta = envelope->delta;
			target = envelope->target;
			velocity = channel->velocity - envelope->delta;


			if ((delta >= 0 && velocity <= target) || (delta < 0 && velocity >= target)) {
				channel->velocity = target;


				if (target == 0) {
					channel->note = -1;
					break;
				} else
					switch (channel->envelope) {
					case 0:
					case 2:

						set_envelope(channel, instrument->envelope, channel->envelope + 1);
						break;
					case 1:
					case 3:

						channel->envelope_samples = -1;
						break;
					}
			} else {

				channel->envelope_samples = envelope->length;
				channel->velocity = velocity;
			}
		}

		if (index == count)
			break;

		if (frac_to_int(channel->offset) >= seg_end) {
			if (instrument->mode & MODE_LOOP) {

				channel->offset -= int_to_frac(seg_end);
				channel->looping = 1;
			} else {

				channel->note = -1;
				break;
			}
		}
	}
}
