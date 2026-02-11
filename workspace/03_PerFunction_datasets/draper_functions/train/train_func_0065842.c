AsTV(CCECBusDevice *device)
{
  if (device && device->GetType() == CEC_DEVICE_TYPE_TV)
    return static_cast<CCECTV *>(device);
  return NULL;
}
