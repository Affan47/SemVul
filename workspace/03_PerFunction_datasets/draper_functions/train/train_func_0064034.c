pck_splitandprocess(Limdfsresources *limdfsresources,
                                const AbstractDfstransformer *adfst)
{
  unsigned long idx;
  unsigned long sumwidth = 0;
  const Indexbounds *parent = &(currentparent(limdfsresources)->lcpitv);
  GtCodetype startcode;

  if (parent->offset < (unsigned long) limdfsresources->genericindex->maxdepth)
  {
    smalldepthbwtrangesplitwithoutspecial(&limdfsresources->bwci,
                                          limdfsresources->genericindex->mbtab,
                                          limdfsresources->alphasize,
                                          parent->code,
                                          (unsigned long) (parent->offset + 1));
    startcode = parent->code * limdfsresources->alphasize;
  } else
  {
    gt_bwtrangesplitwithoutspecial(&limdfsresources->bwci,
                                limdfsresources->rangeOccs,
                                limdfsresources->genericindex->packedindex,
                                parent->leftbound,
                                parent->rightbound);
    startcode = 0;
  }
  for (idx = 0; idx < limdfsresources->bwci.nextfreeBoundswithchar; idx++)
  {
    Indexbounds child;


    parent = &(currentparent(limdfsresources)->lcpitv);
    child.inchar = limdfsresources->bwci.spaceBoundswithchar[idx].inchar;
    child.offset = parent->offset+1;
    child.leftbound = limdfsresources->bwci.spaceBoundswithchar[idx].lbound;
    child.rightbound = limdfsresources->bwci.spaceBoundswithchar[idx].rbound;
    gt_assert(child.inchar < limdfsresources->alphasize);
    child.code = startcode + child.inchar;
    addpathchar(limdfsresources,(unsigned long) parent->offset,child.inchar);
    sumwidth += child.rightbound - child.leftbound;
#ifdef SKDEBUG
    printf("%u-child of ",(unsigned int) child.inchar);
    showLCPinterval(limdfsresources->genericindex->withesa,parent);
    printf(" is ");
    showLCPinterval(limdfsresources->genericindex->withesa,&child);
    printf("\n");
#endif
    processchildinterval(limdfsresources, &child, adfst);
  }
  if (!limdfsresources->nowildcards)
  {
    unsigned long bound;
    Indexbounds child;

    for (bound = parent->leftbound + sumwidth;
         bound < parent->rightbound; bound++)
    {
      GtUchar cc = gt_bwtseqgetsymbol(bound,
                                   limdfsresources->genericindex->packedindex);

      child.offset = parent->offset+1;
      child.code = 0;
      if (cc != (GtUchar) SEPARATOR)
      {
        child.leftbound = bound;
        child.inchar = cc;
        pck_overcontext(limdfsresources,&child,adfst);
      }
    }
  }
}
