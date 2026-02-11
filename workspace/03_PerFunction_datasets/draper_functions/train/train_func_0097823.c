gt_fmfindtextpos (const Fmindex *fm,unsigned long idx)
{
  unsigned long offset = 0;
  GtUchar cc;

  while ((idx & fm->markdistminus1) != 0)
  {
    if (idx == fm->longestsuffixpos || ISSPECIAL(cc = ACCESSBWTTEXT(idx)))
    {
      unsigned long smallestgeq
               = searchsmallestgeq(fm->specpos.spaceGtPairBwtidx,
                                   fm->specpos.spaceGtPairBwtidx +
                                   fm->specpos.nextfreeGtPairBwtidx - 1,
                                   idx);
      return (smallestgeq + offset) % fm->bwtlength;
    }
    idx = fm->tfreq[cc] + fmoccurrence (fm, cc, idx);
    offset++;
  }
  return (fm->markpostable[idx / fm->markdist] + offset) % fm->bwtlength;
}
