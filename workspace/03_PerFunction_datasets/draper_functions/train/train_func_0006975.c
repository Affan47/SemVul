HitsToBestHits(hit_t *hits, int nHits, int iNode, besthit_t *newhits) {
  int i;
  for (i = 0; i < nHits; i++) {
    hit_t *hit = &hits[i];
    besthit_t *bh = &newhits[i];
    bh->i = iNode;
    bh->j = hit->j;
    bh->dist = hit->dist;
    bh->criterion = 1e20;
    bh->weight = -1;
  }
}
