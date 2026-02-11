delBlock(MemBlock *b)
{


  if (d->hashList && !d->hashDirty) {
    quintptr adr = (( quintptr )b->begin) & (~(d->blockSize - 1));
    quintptr end = (( quintptr )b->begin) + d->blockSize;
    while (adr < end) {
      quintptr key = adr >> d->log2;
      key = key & (d->hashSize - 1);
      if (d->hashList[key]) {
	QList<MemBlock *> *list = d->hashList[key];
	QList<MemBlock *>::Iterator it = list->begin();
	QList<MemBlock *>::Iterator endit = list->end();
	for (; it != endit; ++it)
	  if (*it == b) {
	    list->erase(it);
	    break;
	  }
      }
      adr += d->blockSize;
    }
  }
  if (b->older)
    b->older->newer = b->newer;
  if (b->newer)
    b->newer->older = b->older;
  if (b == d->currentBlock) {
    d->currentBlock = 0;
    d->blockOffset = d->blockSize;
  }
  delete b;
  d->num_blocks--;
}
