resolve_cpu(int cpuid)
{
  int i, ncpus;
  int nnodes;
  int *nodes;
  struct route *r;


  nnodes = getntype(0, NT_CAST);
  nodes = (int *) malloc(sizeof(int) * nnodes);
  if (nodes == NULL)
    return (LAMERROR);

  r = (struct route*) malloc(sizeof(struct route) * nnodes);
  if (r == NULL)
    return (LAMERROR);
  getnodes(nodes, nnodes, 0, NT_CAST);
  for (ncpus = i = 0; i < nnodes; i++) {
    r[i].r_nodeid = nodes[i];
    getrent(&r[i]);
    ncpus += r[i].r_ncpus;
  }

  if (cpuid < 0 || cpuid >= ncpus) {
    free(r);
    free(nodes);
    return (LAMERROR);
  }


  for (ncpus = i = 0; i < nnodes; i++) {
    if (cpuid < (ncpus + r[i].r_ncpus))
      break;
    ncpus += r[i].r_ncpus;
  }

  free(r);
  free(nodes);

  return i;
}
