addWord(TextWord *word) {
  TextWord **newPool;
  int wordBaseIdx, newMinBaseIdx, newMaxBaseIdx, baseIdx;
  TextWord *w0, *w1;


  wordBaseIdx = (int)(word->base / textPoolStep);
  if (minBaseIdx > maxBaseIdx) {
    minBaseIdx = wordBaseIdx - 128;
    maxBaseIdx = wordBaseIdx + 128;
    pool = (TextWord **)gmallocn(maxBaseIdx - minBaseIdx + 1,
				 sizeof(TextWord *));
    for (baseIdx = minBaseIdx; baseIdx <= maxBaseIdx; ++baseIdx) {
      pool[baseIdx - minBaseIdx] = NULL;
    }
  } else if (wordBaseIdx < minBaseIdx) {
    newMinBaseIdx = wordBaseIdx - 128;
    newPool = (TextWord **)gmallocn(maxBaseIdx - newMinBaseIdx + 1,
				    sizeof(TextWord *));
    for (baseIdx = newMinBaseIdx; baseIdx < minBaseIdx; ++baseIdx) {
      newPool[baseIdx - newMinBaseIdx] = NULL;
    }
    memcpy(&newPool[minBaseIdx - newMinBaseIdx], pool,
	   (maxBaseIdx - minBaseIdx + 1) * sizeof(TextWord *));
    gfree(pool);
    pool = newPool;
    minBaseIdx = newMinBaseIdx;
  } else if (wordBaseIdx > maxBaseIdx) {
    newMaxBaseIdx = wordBaseIdx + 128;
    pool = (TextWord **)greallocn(pool, newMaxBaseIdx - minBaseIdx + 1,
				  sizeof(TextWord *));
    for (baseIdx = maxBaseIdx + 1; baseIdx <= newMaxBaseIdx; ++baseIdx) {
      pool[baseIdx - minBaseIdx] = NULL;
    }
    maxBaseIdx = newMaxBaseIdx;
  }


  if (cursor && wordBaseIdx == cursorBaseIdx &&
      word->primaryCmp(cursor) > 0) {
    w0 = cursor;
    w1 = cursor->next;
  } else {
    w0 = NULL;
    w1 = pool[wordBaseIdx - minBaseIdx];
  }
  for (; w1 && word->primaryCmp(w1) > 0; w0 = w1, w1 = w1->next) ;
  word->next = w1;
  if (w0) {
    w0->next = word;
  } else {
    pool[wordBaseIdx - minBaseIdx] = word;
  }
  cursor = word;
  cursorBaseIdx = wordBaseIdx;
}
