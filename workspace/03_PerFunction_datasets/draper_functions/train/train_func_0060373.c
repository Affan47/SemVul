compute_peratom()
{
  invoked_peratom = update->ntimestep;


  if (atom->nlocal > nmax) {
    nmax = atom->nmax;
    if (nvalues == 1) {
      memory->destroy(vector);
      memory->create(vector,nmax,"property/atom:vector");
      vector_atom = vector;
    } else {
      memory->destroy(array);
      memory->create(array,nmax,nvalues,"property/atom:array");
      array_atom = array;
    }
  }


  if (nvalues == 1) {
    buf = vector;
    (this->*pack_choice[0])(0);
  } else {
    if (nmax) buf = &array[0][0];
    else buf = NULL;
    for (int n = 0; n < nvalues; n++)
      (this->*pack_choice[n])(n);
  }
}
