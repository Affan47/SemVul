rb_radio_tuner_update (RBRadioTuner *self)
{
	struct v4l2_tuner tuner;
	struct v4l2_control control;
	struct v4l2_frequency frequency;
	gboolean has_changed = FALSE;

	memset (&tuner, 0, sizeof (tuner));
	tuner.index = 0;
	if (ioctl (self->priv->fd, VIDIOC_G_TUNER, &tuner) >= 0) {
		if (self->is_stereo != (tuner.audmode==V4L2_TUNER_MODE_STEREO))
			has_changed = TRUE;
		self->is_stereo = (tuner.audmode==V4L2_TUNER_MODE_STEREO);

		if (self->signal != tuner.signal)
			has_changed = TRUE;
		self->signal = tuner.signal;
	}

	memset (&control, 0, sizeof (control));
	control.id = V4L2_CID_AUDIO_MUTE;
	if (ioctl (self->priv->fd, VIDIOC_G_CTRL, &control) >= 0) {
		control.value = !!control.value;
		if (self->is_muted != control.value)
			has_changed = TRUE;
		self->is_muted = control.value;
	}

	memset (&frequency, 0, sizeof (frequency));
	frequency.tuner = 0;
	if (ioctl (self->priv->fd, VIDIOC_G_FREQUENCY, &frequency) >= 0) {
		if (self->priv->current_frequency != frequency.frequency)
			has_changed = TRUE;
		self->priv->current_frequency = frequency.frequency;
		self->frequency = (double)frequency.frequency
			/ self->priv->freq_mul;
	}

	rb_debug ("Tuner %s", has_changed ? "has changed" : "has not changed");

#if 0
	if (has_changed) {
		g_signal_emit (self, CHANGED);
	}
#endif
}
