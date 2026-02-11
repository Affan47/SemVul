replace(DVPSImageBoxContent *newImageBox)
{
  if (! newImageBox) return;

  OFString aString(newImageBox->getSOPInstanceUID());
  OFListIterator(DVPSImageBoxContent *) first = list_.begin();
  OFListIterator(DVPSImageBoxContent *) last = list_.end();
  while (first != last)
  {
    if (aString == (*first)->getSOPInstanceUID())
    {
      delete (*first);
      first = list_.erase(first);
    }
    else ++first;
  }
  list_.push_back(newImageBox);
}
