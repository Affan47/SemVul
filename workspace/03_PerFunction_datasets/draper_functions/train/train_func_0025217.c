freeSpace(Btree *pBt, MemPage *pPage, int start, int size){
  int end = start + size;
  u16 *pIdx, idx;
  FreeBlk *pFBlk;
  FreeBlk *pNew;
  FreeBlk *pNext;
  int iSize;

  assert( sqlitepager_iswriteable(pPage) );
  assert( size == ROUNDUP(size) );
  assert( start == ROUNDUP(start) );
  assert( pPage->isInit );
  pIdx = &pPage->u.hdr.firstFree;
  idx = SWAB16(pBt, *pIdx);
  while( idx!=0 && idx<start ){
    pFBlk = (FreeBlk*)&pPage->u.aDisk[idx];
    iSize = SWAB16(pBt, pFBlk->iSize);
    if( idx + iSize == start ){
      pFBlk->iSize = SWAB16(pBt, iSize + size);
      if( idx + iSize + size == SWAB16(pBt, pFBlk->iNext) ){
        pNext = (FreeBlk*)&pPage->u.aDisk[idx + iSize + size];
        if( pBt->needSwab ){
          pFBlk->iSize = swab16((u16)swab16(pNext->iSize)+iSize+size);
        }else{
          pFBlk->iSize += pNext->iSize;
        }
        pFBlk->iNext = pNext->iNext;
      }
      pPage->nFree += size;
      return;
    }
    pIdx = &pFBlk->iNext;
    idx = SWAB16(pBt, *pIdx);
  }
  pNew = (FreeBlk*)&pPage->u.aDisk[start];
  if( idx != end ){
    pNew->iSize = SWAB16(pBt, size);
    pNew->iNext = SWAB16(pBt, idx);
  }else{
    pNext = (FreeBlk*)&pPage->u.aDisk[idx];
    pNew->iSize = SWAB16(pBt, size + SWAB16(pBt, pNext->iSize));
    pNew->iNext = pNext->iNext;
  }
  *pIdx = SWAB16(pBt, start);
  pPage->nFree += size;
}
