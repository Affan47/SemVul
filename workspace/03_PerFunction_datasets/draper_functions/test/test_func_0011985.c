compute(int eflag, int vflag)
{
  if (eflag || vflag) {
    ev_setup(eflag,vflag);
  } else evflag = vflag_fdotr = 0;

  const int nall = atom->nlocal + atom->nghost;
  const int nthreads = comm->nthreads;
  const int inum = list->inum;
  double occ = 0.0;

#if defined(_OPENMP)
#pragma omp parallel default(none) shared(eflag,vflag) reduction(+:occ)
#endif
  {
    int ifrom, ito, tid;

    loop_setup_thr(ifrom, ito, tid, inum, nthreads);
    ThrData *thr = fix->get_thr(tid);
    ev_setup_thr(eflag, vflag, nall, eatom, vatom, thr);

    if (evflag) {
      if (eflag) {
        if (force->newton_pair) occ = eval<1,1,1>(ifrom, ito, thr);
        else occ = eval<1,1,0>(ifrom, ito, thr);
      } else {
        if (force->newton_pair) occ = eval<1,0,1>(ifrom, ito, thr);
        else occ = eval<1,0,0>(ifrom, ito, thr);
      }
    } else {
      if (force->newton_pair) occ = eval<0,0,1>(ifrom, ito, thr);
      else occ = eval<0,0,0>(ifrom, ito, thr);
    }

    reduce_thr(this, eflag, vflag, thr);
  }

  if (eflag_global) pvector[0] = occ;
}
