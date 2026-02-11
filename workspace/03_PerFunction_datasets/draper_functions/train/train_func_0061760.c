numberOfImageReferences()
{
  size_t result=0;
  OFListIterator(DVPSReferencedSeries *) first = list_.begin();
  OFListIterator(DVPSReferencedSeries *) last = list_.end();
  while (first != last)
  {
    result += (*first)->numberOfImageReferences();
    ++first;
  }
  return result;
}
