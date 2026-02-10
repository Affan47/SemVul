gt_ppt_hit_new(GtStrand strand, GtPPTResults *r)
{
  GtPPTHit *h = gt_calloc((size_t) 1, sizeof (GtPPTHit));
  gt_assert(h);
  h->strand = strand;
  h->res = r;
  h->score = 0.0;
  return h;
}
