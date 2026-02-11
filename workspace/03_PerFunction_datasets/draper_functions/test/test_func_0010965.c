pseudoprob(p, LINK)
thisperson **p;
struct LOC_likelihood *LINK;
{
  thisperson *WITH;

  WITH = *p;
  if (!(WITH->newgenexists))
    if ((*p)->pa == NULL) {
      LINK->nuscale++;
      if (WITH->inloop > 0) {
	LINK->nuscale--;
      }
    }
}
