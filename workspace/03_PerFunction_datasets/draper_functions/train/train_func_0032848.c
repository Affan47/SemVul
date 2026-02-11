setAllImagesToDefault()
{
  OFCondition result = EC_Normal;
  OFListIterator(DVPSImageBoxContent *) first = list_.begin();
  OFListIterator(DVPSImageBoxContent *) last = list_.end();
  while (first != last)
  {
    result = (*first)->setDefault();
    ++first;
    if (EC_Normal != result) return result;
  }
  return result;
}
