nextPage()
{
  long nextPageOffset;
  int currentPacket;

  if(d->pages.isEmpty()) {
    currentPacket = 0;
    nextPageOffset = find("OggS");
    if(nextPageOffset < 0)
      return false;
  }
  else {
    if(d->currentPage->header()->lastPageOfStream())
      return false;

    if(d->currentPage->header()->lastPacketCompleted())
      currentPacket = d->currentPage->firstPacketIndex() + d->currentPage->packetCount();
    else
      currentPacket = d->currentPage->firstPacketIndex() + d->currentPage->packetCount() - 1;

    nextPageOffset = d->currentPage->fileOffset() + d->currentPage->size();
  }


  d->currentPage = new Page(this, nextPageOffset);

  if(!d->currentPage->header()->isValid()) {
    delete d->currentPage;
    d->currentPage = 0;
    return false;
  }

  d->currentPage->setFirstPacketIndex(currentPacket);

  if(d->pages.isEmpty())
    d->streamSerialNumber = d->currentPage->header()->streamSerialNumber();

  d->pages.append(d->currentPage);


  for(uint i = 0; i < d->currentPage->packetCount(); i++) {
    uint currentPacket = d->currentPage->firstPacketIndex() + i;
    if(d->packetToPageMap.size() <= currentPacket)
      d->packetToPageMap.push_back(List<int>());
    d->packetToPageMap[currentPacket].append(d->pages.size() - 1);
  }

  return true;
}
