DisposeOutPts(OutPt*& pp)
{
  if (pp == 0) return;
  pp->prev->next = 0;
  while( pp )
  {
    OutPt *tmpPp = pp;
    pp = pp->next;
    delete tmpPp ;
  }
}
