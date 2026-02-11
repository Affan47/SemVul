addpathchar(Limdfsresources *limdfsresources,unsigned long idx,
                        GtUchar cc)
{
  if (limdfsresources->currentpathspace != NULL)
  {
    gt_assert(idx < limdfsresources->allocatedpathspace);
    limdfsresources->currentpathspace[idx] = cc;
  }
}
