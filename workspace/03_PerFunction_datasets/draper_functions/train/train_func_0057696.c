Start ()
{
  if (!is_active) {
    if (devices_nbr == 0) {
      videoinput_core->set_stream_config(frameWidth, frameHeight, frameRate);
      videoinput_core->start_stream();
    }
    is_active = true;
    devices_nbr++;
  }

  return true;
}
