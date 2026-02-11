makesuccs(Mergertrienode *newbranch,Mergertrienode *first,
                      Mergertrienode *second)
{
  second->rightsibling = NULL;
  first->rightsibling = second;
  SETFIRSTCHILD(newbranch,first);
  SHOWNODERELATIONS(second);
  SHOWNODERELATIONS(first);
  SHOWNODERELATIONS(newbranch);
}
