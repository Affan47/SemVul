incrementdistribcounts(GtArrayCountwithpositions *occdistribution,
                                   unsigned long countocc,unsigned long value)
{
  if (countocc >= occdistribution->allocatedCountwithpositions)
  {
    const unsigned long addamount = 128UL;
    unsigned long idx;

    occdistribution->spaceCountwithpositions
      = gt_realloc(occdistribution->spaceCountwithpositions,
                   sizeof *occdistribution->spaceCountwithpositions
                   * (countocc+addamount));
    for (idx=occdistribution->allocatedCountwithpositions;
         idx<countocc+addamount; idx++)
    {
      occdistribution->spaceCountwithpositions[idx].occcount = 0;
      occdistribution->spaceCountwithpositions[idx].positionlist = NULL;
    }
    occdistribution->allocatedCountwithpositions = countocc+addamount;
  }
  if (countocc + 1 > occdistribution->nextfreeCountwithpositions)
  {
    occdistribution->nextfreeCountwithpositions = countocc+1;
  }
  occdistribution->spaceCountwithpositions[countocc].occcount += value;
}
