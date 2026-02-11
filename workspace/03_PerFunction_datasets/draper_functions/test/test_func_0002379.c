createNode()
{

  NodeT *np;

  np = (NodeT *)malloc(sizeof(NodeT));
  if(!np)
    {
      perror("weighbor::tree::createNode");
      exit(1);
    }

  np->name=0;
  np->rho = 0.0;
  np->ind = 0;
  np->child_l = NULL;
  np->child_r = NULL;
  np->cind_r = -1;
  np->cind_l = -1;

  return(np);

}
