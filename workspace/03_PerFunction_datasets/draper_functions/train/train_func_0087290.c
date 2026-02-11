update_it_envelopes(IT_PLAYING *playing)
{
	IT_ENVELOPE *envelope = &playing->env_instrument->volume_envelope;
	IT_PLAYING_ENVELOPE *pe = &playing->volume_envelope;

	if (update_it_envelope(playing, envelope, pe)) {
		playing->flags |= IT_PLAYING_FADING;
		if (pe->value == 0)
			playing->flags |= IT_PLAYING_DEAD;
	}

	update_it_envelope(playing, &playing->env_instrument->pan_envelope, &playing->pan_envelope);
	update_it_envelope(playing, &playing->env_instrument->pitch_envelope, &playing->pitch_envelope);
}
