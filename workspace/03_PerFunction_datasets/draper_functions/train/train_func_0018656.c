search_ngram_core(NGRAM_INFO *ndata, int n, NNID nid_prev, WORD_ID wkey)
{
  NGRAM_TUPLE_INFO *t, *tprev;
  NNID nnid;
  NNID left,right,mid;
  NNID x;

  if (ndata->bigram_index_reversed && n == 2) {


    x = nid_prev;
    nid_prev = wkey;
    wkey = x;
  }

  t = &(ndata->d[n-1]);
  tprev = &(ndata->d[n-2]);

  if (tprev->ct_compaction) {
    nnid = tprev->nnid2ctid_upper[nid_prev];
    if (nnid == NNID_INVALID_UPPER) return (NNID_INVALID);
    nnid = (nnid << 16) + (NNID)(tprev->nnid2ctid_lower[nid_prev]);
  } else {
    nnid = nid_prev;
  }
  if (t->is24bit) {
    left = t->bgn_upper[nnid];
    if (left == NNID_INVALID_UPPER) return (NNID_INVALID);
    left = (left << 16) + (NNID)(t->bgn_lower[nnid]);
  } else {
    left = t->bgn[nnid];
    if (left == NNID_INVALID) return (NNID_INVALID);
  }
  right = left + t->num[nnid] - 1;

  while(left < right) {
    mid = (left + right) / 2;
    if (t->nnid2wid[mid] < wkey) {
      left = mid + 1;
    } else {
      right = mid;
    }
  }
  if (t->nnid2wid[left] == wkey) {
    return (left);
  } else {
    return (NNID_INVALID);
  }
}
