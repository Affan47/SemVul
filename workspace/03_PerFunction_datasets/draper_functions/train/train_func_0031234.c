propSet(const char *property, int value, int idx)
{
  OfxStatus stat = gPropSuite->propSetInt(_propHandle, property, idx, value);
  OFX::logError(stat != kOfxStatOK, "Failed on setting int property %s[%d] to %d, host returned status '%s';", property, idx, value, mapStatus(stat));
  if(stat == kOfxStatOK && _propLogMessages <= 0)
    OFX::logPrint("Set int property %s[%d] = %d;", property, idx, value);
  return stat;
}
