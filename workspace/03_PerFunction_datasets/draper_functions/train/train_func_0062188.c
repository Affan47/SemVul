getActivationGroup(const char *layer, size_t idx, OFBool isCurve)
{
  if (layer==NULL) return 0;

  Uint16 group;
  OFString aString(layer);
  OFListIterator(DVPSOverlayCurveActivationLayer *) first = list_.begin();
  OFListIterator(DVPSOverlayCurveActivationLayer *) last = list_.end();
  while (first != last)
  {
    if (aString == (*first)->getActivationLayer())
    {
      group = (*first)->getRepeatingGroup();
      if (((isCurve) && (group < 0x6000)) || ((!isCurve) && (group >= 0x6000)))
      {
      	if (idx==0) return group; else idx--;
      }
    }
    ++first;
  }
  return 0;
}
