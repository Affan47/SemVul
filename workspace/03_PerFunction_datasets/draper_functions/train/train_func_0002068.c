_sci_midi_process_state(base_song_iterator_t *self, unsigned char *buf, int *result,
			song_iterator_channel_t *channel,
			int flags)
{
	CHECK_FOR_END(0);

	switch (channel->state) {

	case SI_STATE_PCM: {
		if (*(self->data + channel->offset) == 0
		    && *(self->data + channel->offset + 1) == SCI_MIDI_EOT)

			channel->state = SI_STATE_PCM_MAGIC_DELTA;
		else
			channel->state = SI_STATE_DELTA_TIME;
		return SI_PCM;
	}

	case SI_STATE_PCM_MAGIC_DELTA: {
		sfx_pcm_config_t format;
		int offset;
		unsigned int size;
		int delay;
		if (_sci0_get_pcm_data((sci0_song_iterator_t *) self, &format, &offset, &size))
			return SI_FINISHED;
		channel->state = SI_STATE_FINISHED;
		delay = (size * 50 + format.rate - 1) / format.rate;

		fprintf(stderr, "delaying %d ticks\n", delay);
		return delay;
	}

	case SI_STATE_UNINITIALISED:
		fprintf(stderr, SIPFX "Attempt to read command from uninitialized iterator!\n");
		self->init((song_iterator_t *) self);
		return self->next((song_iterator_t *) self, buf, result);

	case SI_STATE_FINISHED:
		return SI_FINISHED;

	case SI_STATE_DELTA_TIME: {
		int offset;
		int ticks = _parse_ticks(self->data + channel->offset,
					 &offset,
					 self->size - channel->offset);

		channel->offset += offset;
		channel->delay += ticks;
		channel->timepos_increment = ticks;

		CHECK_FOR_END(0);

		channel->state = SI_STATE_COMMAND;

		if (ticks)
			return ticks;
	}


	case SI_STATE_COMMAND: {
		int retval;
		channel->total_timepos += channel->timepos_increment;
		channel->timepos_increment = 0;

		retval = _parse_sci_midi_command(self, buf, result,
						 channel, flags);

		if (retval == SI_FINISHED) {
			if (self->active_channels)
				--(self->active_channels);
#ifdef DEBUG_DECODING
			fprintf(stderr, "%s L%d: (%p):%d Finished channel, %d channels left\n",
				__FILE__, __LINE__, self, channel->id,
				self->active_channels);
#endif

			if (self->active_channels) {
				return self->next((song_iterator_t *) self, buf, result);
			}


			self->loops = 0;
		}

		return retval;
	}

	default:
		fprintf(stderr, SIPFX "Invalid iterator state %d!\n",
			channel->state);
		BREAKPOINT();
		return SI_FINISHED;
	}
}
