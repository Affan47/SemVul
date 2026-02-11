pack_comm(int n, int *list, double *buf,
                          int pbc_flag, int *pbc)
{
  int i,j,m;
  double dx,dy,dz;
  double *quat;

  m = 0;
  if (pbc_flag == 0) {
    for (i = 0; i < n; i++) {
      j = list[i];
      buf[m++] = x[j][0];
      buf[m++] = x[j][1];
      buf[m++] = x[j][2];
      if (tri[j] >= 0) {
        quat = bonus[tri[j]].quat;
        buf[m++] = quat[0];
        buf[m++] = quat[1];
        buf[m++] = quat[2];
        buf[m++] = quat[3];
      }
    }
  } else {
    if (domain->triclinic == 0) {
      dx = pbc[0]*domain->xprd;
      dy = pbc[1]*domain->yprd;
      dz = pbc[2]*domain->zprd;
    } else {
      dx = pbc[0]*domain->xprd + pbc[5]*domain->xy + pbc[4]*domain->xz;
      dy = pbc[1]*domain->yprd + pbc[3]*domain->yz;
      dz = pbc[2]*domain->zprd;
    }
    for (i = 0; i < n; i++) {
      j = list[i];
      buf[m++] = x[j][0] + dx;
      buf[m++] = x[j][1] + dy;
      buf[m++] = x[j][2] + dz;
      if (tri[j] >= 0) {
        quat = bonus[tri[j]].quat;
        buf[m++] = quat[0];
        buf[m++] = quat[1];
        buf[m++] = quat[2];
        buf[m++] = quat[3];
      }
    }
  }

  return m;
}
