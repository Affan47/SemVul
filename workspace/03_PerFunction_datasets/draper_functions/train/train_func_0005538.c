precollapsedown(p, LINK)
thisperson *p;
struct LOC_likelihood *LINK;
{
  thisperson *childonlist;

  if (p->pa == NULL)
    return;
  p->up = true;
  precollapseup(p->pa);
  if (p->pa->loopdepend || p->ma->loopdepend) {
    p->loopdepend = true;
    p->loopneeded = false;
  }
  childonlist = p->pa->foff;
  while (childonlist != NULL) {
    if (childonlist->loopdepend) {
      p->loopdepend = true;
      p->loopneeded = false;
    }
    if (p->male)
      childonlist = childonlist->nextpa;
    else
      childonlist = childonlist->nextma;
  }
}
