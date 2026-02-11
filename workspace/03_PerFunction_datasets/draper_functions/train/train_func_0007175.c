initparentcopy(Limdfsresources *limdfsresources,
                           const AbstractDfstransformer *adfst)
{
  if (!limdfsresources->keepexpandedonstack)
  {
    if (adfst->copyLimdfsstate == NULL)
    {
      memcpy(limdfsresources->copyofcopyofparentstate,
             limdfsresources->copyofparent.aliasstate,
             adfst->sizeofdfsstate);
    } else
    {
      adfst->copyLimdfsstate(limdfsresources->copyofcopyofparentstate,
                             limdfsresources->copyofparent.aliasstate,
                             limdfsresources->dfsconstinfo);
    }
  }
}
