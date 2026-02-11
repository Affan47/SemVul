multi_map(void)
{
  int i;
  struct ilist *inputs = NULL;
  struct ilist *ip;

  Bsize = 0;


  for (i = 0; i < Asize; i++) {
    if (Alists[i] != NULL) {
      struct glist *d;
      for (d = Alists[i]; d != NULL; d= d->next) {
	for (ip = d->v; ip != NULL; ip = ip->next) {
	  if (Alists[ip->i] == NULL)
	    inputs = iset_add(ip->i, inputs);
	}
      }
    }
  }

  A_to_B = calloc(Asize, sizeof(int));

  for (i = 0; i < Asize; i++)
    A_to_B[i] = -1;

  for (ip = inputs; ip != NULL; ip = ip->next) {
    A_to_B[ip->i] = Bsize++;
  }
  free_ilist_list(inputs);


  for (i = 0; i < Asize; i++) {
    if (Alists[i] != NULL) {
      A_to_B[i] = Bsize++;
    }
  }


  Blists = calloc(Bsize, sizeof(struct glist *));
  B_to_A = calloc(Bsize, sizeof(int));

  for (i = 0; i < Asize; i++) {
    if (Alists[i] != NULL) {
      struct glist *d;
      Blists[A_to_B[i]] = copy_glist(Alists[i]);
      for (d = Blists[A_to_B[i]]; d != NULL; d= d->next) {
	d->v = copy_ilist(d->v);
	for (ip = d->v; ip != NULL; ip = ip->next) {
	  ip->i = A_to_B[ip->i];
	}
      }
    }
  }


  for (i = 0; i < Asize; i++)
    if (A_to_B[i] != -1)
      B_to_A[A_to_B[i]] = i;

}
