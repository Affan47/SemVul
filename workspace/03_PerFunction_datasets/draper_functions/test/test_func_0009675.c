MatchFinder_ReadIfRequired(CMatchFinder *p)
{
  if (p->streamEndWasReached)
    return;
  if (p->keepSizeAfter >= p->streamPos - p->pos)
    MatchFinder_ReadBlock(p);
}
