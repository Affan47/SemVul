runlimdfs(Limdfsresources *limdfsresources,
                      const AbstractDfstransformer *adfst)
{
  Lcpintervalwithinfo *stackptr;

  gt_assert(adfst->sizeofdfsstate <=
            sizeof (limdfsresources->copyofparent.aliasstate));
  limdfsresources->numberofmatches = 0;
  initlcpinfostack(limdfsresources,adfst);
  while (limdfsresources->stack.nextfreeLcpintervalwithinfo > 0)
  {
    gt_assert(limdfsresources->stack.spaceLcpintervalwithinfo != NULL);


    stackptr = limdfsresources->stack.spaceLcpintervalwithinfo +
               limdfsresources->stack.nextfreeLcpintervalwithinfo - 1;
    SHOWSTACKTOP(stackptr);
    if (limdfsresources->keepexpandedonstack)
    {
      if (stackptr->keeponstack)
      {
        limdfsresources->parentindex
          = limdfsresources->stack.nextfreeLcpintervalwithinfo - 1;
      } else
      {
        limdfsresources->stack.nextfreeLcpintervalwithinfo--;
        continue;
      }
    } else
    {

      if (adfst->copyLimdfsstate == NULL)
      {
        limdfsresources->copyofparent = *stackptr;
      } else
      {
        limdfsresources->copyofparent.lcpitv = stackptr->lcpitv;
        adfst->copyLimdfsstate(limdfsresources->copyofparent.aliasstate,
                               stackptr->aliasstate,
                               limdfsresources->dfsconstinfo);
      }

    }
    if (currentparent(limdfsresources)->lcpitv.offset > 0)
    {
      addpathchar(limdfsresources,
                  (unsigned long)
                   (currentparent(limdfsresources)->lcpitv.offset-1),
                  currentparent(limdfsresources)->lcpitv.inchar);
    }
    gt_assert(limdfsresources->stack.nextfreeLcpintervalwithinfo > 0);

    if (limdfsresources->keepexpandedonstack)
    {
      stackptr->keeponstack = false;
    } else
    {
      limdfsresources->stack.nextfreeLcpintervalwithinfo--;
    }
    (limdfsresources->genericindex->withesa
        ? esa_splitandprocess
        : pck_splitandprocess) (limdfsresources,adfst);
  }
  if (adfst->extractdfsconstinfo != NULL)
  {
    adfst->extractdfsconstinfo(limdfsresources->processresult,
                               limdfsresources,
                               limdfsresources->patterninfo,
                               limdfsresources->dfsconstinfo);
  }
}
