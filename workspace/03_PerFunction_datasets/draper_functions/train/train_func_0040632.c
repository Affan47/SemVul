processbranchedge_elcp(bool firstsucc,
                                  unsigned long fatherdepth,
                                  Dfsinfo *afather,
                                  Dfsinfo *ason,
                                  Dfsstate *astate,
                                  GT_UNUSED GtError *err)
{
  Lcpinterval *father = (Lcpinterval *) afather;
  Lcpinterval *son = (Lcpinterval *) ason;
  Elcpstate *state = (Elcpstate *) astate;

  if (son != NULL)
  {
    showbranchingedgeDFS(firstsucc,fatherdepth,father->left,son->offset,
                       son->left);
  } else
  {
    showbranchingedgeDFS(firstsucc,fatherdepth,father->left,
                       state->lastcompletenode.offset,
                       state->lastcompletenode.left);
  }
  return 0;
}
