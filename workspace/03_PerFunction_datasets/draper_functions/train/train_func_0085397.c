hit_sorter_by_seqidx(const void *vh1, const void *vh2)
{
  P7_HIT *h1 = *((P7_HIT **) vh1);
  P7_HIT *h2 = *((P7_HIT **) vh2);

  if      (h1->seqidx > h2->seqidx) return  1;
  else if (h1->seqidx < h2->seqidx) return -1;

  int dir1 = (h1->dcl[0].iali < h1->dcl[0].jali ? 1 : -1);
  int dir2 = (h2->dcl[0].iali < h2->dcl[0].jali ? 1 : -1);

  if (dir1 != dir2) return dir2;
  else              return  (h1->dcl[0].iali > h2->dcl[0].iali ? 1 : -1 );
}
