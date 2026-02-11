restart(char *buf)
{
  int n = 0;
  double *rlist = (double *) buf;


  seed = static_cast<int> (0.5*rlist[n++]);

  for (int ixnode = 0; ixnode < nxnodes; ixnode++)
    for (int iynode = 0; iynode < nynodes; iynode++)
      for (int iznode = 0; iznode < nznodes; iznode++)
        T_electron[ixnode][iynode][iznode] = rlist[n++];

  delete random;
  random = new RanMars(lmp,seed+comm->me);
}
