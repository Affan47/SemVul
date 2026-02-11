blindtrie_extractleafnode(GtBlindtrie *blindtrie,
                                                     GtBlindtriesnodeptr head)
{
  gt_assert(!blindtrie_isleaf(blindtrie,head));
  do
  {
    head = blindtrie_firstchild_get(blindtrie,head);
  } while (!blindtrie_isleaf(blindtrie,head));
  return head;
}
