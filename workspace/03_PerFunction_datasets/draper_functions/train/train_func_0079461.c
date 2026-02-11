gst_audio_clock_dispose (GObject * object)
{
  GstAudioClock *clock = GST_AUDIO_CLOCK (object);

  if (clock->destroy_notify && clock->user_data)
    clock->destroy_notify (clock->user_data);
  clock->destroy_notify = NULL;
  clock->user_data = NULL;

  G_OBJECT_CLASS (parent_class)->dispose (object);
}
