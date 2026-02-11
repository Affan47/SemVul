ClockwiseBspTree(node_t *root)
{
  int i;

  (void) root;

  DisplayTicker();

  for (i=0; i < num_subsecs; i++)
  {
    subsec_t *sub = LookupSubsec(i);

    ClockwiseOrder(sub);
    RenumberSubsecSegs(sub);


    SanityCheckClosed(sub);
    SanityCheckSameSector(sub);
    SanityCheckHasRealSeg(sub);
  }
}
