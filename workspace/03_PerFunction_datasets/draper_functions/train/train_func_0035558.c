disconnect_chain (GstPlayAudioChain * chain, GstPlaySink * playsink)
{
  if (chain) {
    if (chain->volume)
      g_signal_handlers_disconnect_by_func (chain->volume, notify_volume_cb,
          playsink);
    if (chain->mute)
      g_signal_handlers_disconnect_by_func (chain->mute, notify_mute_cb,
          playsink);
  }
}
