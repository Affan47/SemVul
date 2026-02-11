deleteMultipleImages(size_t number)
{
  OFListIterator(DVPSImageBoxContent *) first = list_.begin();
  OFListIterator(DVPSImageBoxContent *) last = list_.end();
  while ((first != last)&&(number--))
  {
    delete (*first);
    first = list_.erase(first);
  }
  return EC_Normal;
}
