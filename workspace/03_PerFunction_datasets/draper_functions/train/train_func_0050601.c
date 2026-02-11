read(DcmItem &dset, Uint16 ovGroup)
{
  OFCondition result = EC_Normal;
  DcmStack stack;

  repeatingGroup = ovGroup;
  activationLayer.setGTag(repeatingGroup);
  READ_FROM_DATASET(DcmCodeString, activationLayer)

  if (activationLayer.getVM() > 1)
  {
    result=EC_IllegalCall;
    DCMPSTAT_INFO("presentation state contains a curve or overlay activation layer with VM > 1");
  }

  return result;
}
