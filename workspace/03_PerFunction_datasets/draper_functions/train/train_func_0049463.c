operator=(const DcmPixelData &obj)
{
  if (this != &obj)
  {
    DcmPolymorphOBOW::operator=(obj);
    existUnencapsulated = obj.existUnencapsulated;
    alwaysUnencapsulated = obj.alwaysUnencapsulated;
    unencapsulatedVR = obj.unencapsulatedVR;
    pixelSeqForWrite = NULL;
    repList.clear();
    repListEnd = repList.end();
    original = repListEnd;
    current = original;
    recalcVR();
    DcmRepresentationListConstIterator oldEnd(obj.repList.end());
    DcmRepresentationListConstIterator it(obj.repList.begin());
    while (it != oldEnd)
    {
        DcmRepresentationEntry *repEnt = new DcmRepresentationEntry(**it);
        repList.push_back(repEnt);
        if (it == obj.original) original = --repList.end();
        if (it == current)
        {
            current = --repList.end();
            recalcVR();
        }
        ++it;
    }

  }
  return *this;
}
