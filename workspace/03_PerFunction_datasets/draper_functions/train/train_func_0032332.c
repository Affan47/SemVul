makevalues(pointarray treenode, long *zeros, unsigned char *zeros2,
                        boolean usertree)
{


  long i, j;
  unsigned char ns=0;
  node *p;

  setuptree(treenode, nonodes, usertree);
  for (i = 0; i < spp; i++)
    alloctip(treenode[i], zeros, zeros2);
  if (!usertree) {
    for (i = spp; i < nonodes; i++) {
      p = treenode[i];
      do {
        allocdiscnontip(p, zeros, zeros2, endsite);
        p = p->next;
      } while (p != treenode[i]);
    }
  }
  for (j = 0; j < endsite; j++) {
    for (i = 0; i < spp; i++) {
      switch (y[i][alias[j] - 1]) {

      case '0':
        ns = 1 << zero;
        break;

      case '1':
        ns = 1 << one;
        break;

      case '2':
        ns = 1 << two;
        break;

      case '3':
        ns = 1 << three;
        break;

      case '4':
        ns = 1 << four;
        break;

      case '5':
        ns = 1 << five;
        break;

      case '6':
        ns = 1 << six;
        break;

      case '7':
        ns = 1 << seven;
        break;

      case '?':
        ns = (1 << zero) | (1 << one) | (1 << two) | (1 << three) |
               (1 << four) | (1 << five) | (1 << six) | (1 << seven);
        break;
      }
      treenode[i]->discbase[j] = ns;
      treenode[i]->numsteps[j] = 0;
    }
  }
}
