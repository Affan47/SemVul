gst_play_sink_get_volume (GstPlaySink * playsink)
{
  gdouble result;
  GstPlayAudioChain *chain;

  GST_PLAY_SINK_LOCK (playsink);
  chain = (GstPlayAudioChain *) playsink->audiochain;
  result = playsink->volume;
  if (chain && chain->volume) {
    if (chain->mute || !playsink->mute) {
      g_object_get (chain->volume, "volume", &result, NULL);
      playsink->volume = result;
    }
  }
  GST_PLAY_SINK_UNLOCK (playsink);

  return result;
}
