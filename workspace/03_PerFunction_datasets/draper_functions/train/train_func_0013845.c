e_tally_thr(Pair * const pair, const int i, const int j,
                         const int nlocal, const int newton_pair,
                         const double evdwl, const double ecoul, ThrData * const thr)
{
  if (pair->eflag_global) {
    if (newton_pair) {
      thr->eng_vdwl += evdwl;
      thr->eng_coul += ecoul;
    } else {
      const double evdwlhalf = 0.5*evdwl;
      const double ecoulhalf = 0.5*ecoul;
      if (i < nlocal) {
        thr->eng_vdwl += evdwlhalf;
        thr->eng_coul += ecoulhalf;
      }
      if (j < nlocal) {
        thr->eng_vdwl += evdwlhalf;
        thr->eng_coul += ecoulhalf;
      }
    }
  }
  if (pair->eflag_atom) {
    const double epairhalf = 0.5 * (evdwl + ecoul);
    if (newton_pair || i < nlocal) thr->eatom_pair[i] += epairhalf;
    if (newton_pair || j < nlocal) thr->eatom_pair[j] += epairhalf;
  }
}
