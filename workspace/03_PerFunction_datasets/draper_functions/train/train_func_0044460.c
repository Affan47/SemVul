updateClipGC(GC gc_)
{
  MSNodeItem *hp=_clipGCListHead.address();
  MSNodeItem *np=hp;
  MSClipArea *clip;

  while ((np=np->next())!=hp)
   {
     clip=(MSClipArea *)np->data();
     if (clip!=0&&clip->clipID()==gc_)
      {
	if (clip==activeClip()) unsetClip();
	delete clip;
	delete np;
	np=hp;
      }
   }
  clip=new MSClipArea(gc_);
  np=new MSNodeItem((void *)clip);
  np->insert(hp->next());
  _clipCount++;
  return clip;
}
