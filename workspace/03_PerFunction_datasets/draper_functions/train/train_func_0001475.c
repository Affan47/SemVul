start (unsigned channels, unsigned samplerate, unsigned bits_per_sample)
{
  yield = true;
  PWaitAndSignal m_pri(core_mutex[primary]);

  if (current_primary_config.active) {
    PTRACE(1, "AudioOutputCore\tTrying to start output device although already started");
    return;
  }

  internal_set_manager(primary, desired_primary_device);

  average_level = 0;
  internal_open(primary, channels, samplerate, bits_per_sample);
  current_primary_config.active = true;
  current_primary_config.channels = channels;
  current_primary_config.samplerate = samplerate;
  current_primary_config.bits_per_sample = bits_per_sample;
  current_primary_config.buffer_size = 0;
  current_primary_config.num_buffers = 0;
}
