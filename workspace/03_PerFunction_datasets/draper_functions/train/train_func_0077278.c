set_volume (AudioOutputPS ps, unsigned volume)
{
  PWaitAndSignal m_vol(volume_mutex);

  if (ps == primary) {
    desired_primary_volume = volume;
  }
}
