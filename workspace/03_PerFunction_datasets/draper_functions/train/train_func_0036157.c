lam_ssi_coll_shmem_get_num_cpu()
{
  int4 node;
  int n_index, n_flags, argc, cpus, onln_cpus;
  int *pnodes;
  char **argv1;
  struct route r;
  static int4 nlinks;
  static struct dolink	*links;

  if (ldogetlinks(&links, &nlinks))
    return LAMERROR;

  pnodes = (int4 *) malloc((unsigned) (nlinks * sizeof(int4)));
  if (pnodes == 0)
    return LAMERROR;

  if (getnodes(pnodes, nlinks, 0, NT_CAST))
    return LAMERROR;

  argc = 2;
  argv1 = (char**) malloc(2 * sizeof(char*));
  argv1[0] = (char*) malloc(2 * sizeof(char));
  strcpy(argv1[0],"a");
  argv1[1] = (char*) malloc(sizeof(char) * 2);
  strcpy(argv1[1],"h");
  if (nid_parse(&argc, argv1) != 0)
    return LAMERROR;

  nid_get(&n_index, &node, &n_flags);
  if (n_index != 0) {
    free(argv1[0]);
    free(argv1[1]);
    free(argv1);
    free(pnodes);
    free(links);
    nid_free();
    return LAMERROR;
  }
  else {
    if (node == LOCAL)
      node = getnodeid();
    r.r_nodeid = node;
    getrent(&r);
    cpus = r.r_ncpus;
  }
  if ((onln_cpus = lam_get_ncpus()) < cpus)
    cpus = onln_cpus;

  free(argv1[0]);
  free(argv1[1]);
  free(argv1);
  free(pnodes);
  free(links);
  nid_free();
  return cpus;
}
