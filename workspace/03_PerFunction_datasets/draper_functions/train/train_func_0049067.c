check_distance()
{
  double delx,dely,delz,rsq;
  double delta,deltasq,delta1,delta2;

  if (boxcheck) {
    if (triclinic == 0) {
      delx = bboxlo[0] - boxlo_hold[0];
      dely = bboxlo[1] - boxlo_hold[1];
      delz = bboxlo[2] - boxlo_hold[2];
      delta1 = sqrt(delx*delx + dely*dely + delz*delz);
      delx = bboxhi[0] - boxhi_hold[0];
      dely = bboxhi[1] - boxhi_hold[1];
      delz = bboxhi[2] - boxhi_hold[2];
      delta2 = sqrt(delx*delx + dely*dely + delz*delz);
      delta = 0.5 * (skin - (delta1+delta2));
      deltasq = delta*delta;
    } else {
      domain->box_corners();
      delta1 = delta2 = 0.0;
      for (int i = 0; i < 8; i++) {
        delx = corners[i][0] - corners_hold[i][0];
        dely = corners[i][1] - corners_hold[i][1];
        delz = corners[i][2] - corners_hold[i][2];
        delta = sqrt(delx*delx + dely*dely + delz*delz);
        if (delta > delta1) delta1 = delta;
        else if (delta > delta2) delta2 = delta;
      }
      delta = 0.5 * (skin - (delta1+delta2));
      deltasq = delta*delta;
    }
  } else deltasq = triggersq;

  double **x = atom->x;
  int nlocal = atom->nlocal;
  if (includegroup) nlocal = atom->nfirst;

  int flag = 0;
  for (int i = 0; i < nlocal; i++) {
    delx = x[i][0] - xhold[i][0];
    dely = x[i][1] - xhold[i][1];
    delz = x[i][2] - xhold[i][2];
    rsq = delx*delx + dely*dely + delz*delz;
    if (rsq > deltasq) flag = 1;
  }

  int flagall;
  MPI_Allreduce(&flag,&flagall,1,MPI_INT,MPI_MAX,world);
  if (flagall && ago == MAX(every,delay)) ndanger++;
  return flagall;
}
