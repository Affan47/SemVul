AsPlaybackDevice(CCECBusDevice *device)
{
  if (device &&
      (device->GetType() == CEC_DEVICE_TYPE_PLAYBACK_DEVICE ||
       device->GetType() == CEC_DEVICE_TYPE_RECORDING_DEVICE))
    return static_cast<CCECPlaybackDevice *>(device);
  return NULL;
}
