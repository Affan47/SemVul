set_device(const VideoInputDevice & device, int channel, VideoInputFormat format)
{
  PWaitAndSignal m(core_mutex);
  internal_set_device(device, channel, format);
  desired_device  = device;
}
