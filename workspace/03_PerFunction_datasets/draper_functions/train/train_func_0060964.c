findDisplayedArea(const char *instanceUID, unsigned long frame)
{
  OFListIterator(DVPSDisplayedArea *) first = list_.begin();
  OFListIterator(DVPSDisplayedArea *) last = list_.end();
  while (first != last)
  {
    if ((*first)->isApplicable(instanceUID, frame)) return (*first);
    ++first;
  }
  return NULL;
}
