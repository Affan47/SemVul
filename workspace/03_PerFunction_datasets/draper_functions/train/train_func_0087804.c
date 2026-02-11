unpack_border_vel(int n, int first, double *buf)
{
  int i,k,m,last;
  int omega_flag = atom->omega_flag;
  int angmom_flag = atom->angmom_flag;

  m = 0;
  last = first + n;
  for (i = first; i < last; i++) {
    if (i == nmax) grow(0);
    x[i][0] = buf[m++];
    x[i][1] = buf[m++];
    x[i][2] = buf[m++];
    tag[i] = static_cast<int> (buf[m++]);
    type[i] = static_cast<int> (buf[m++]);
    mask[i] = static_cast<int> (buf[m++]);
    v[i][0] = buf[m++];
    v[i][1] = buf[m++];
    v[i][2] = buf[m++];
    if (omega_flag) {
      omega[i][0] = buf[m++];
      omega[i][1] = buf[m++];
      omega[i][2] = buf[m++];
    }
    if (angmom_flag) {
      angmom[i][0] = buf[m++];
      angmom[i][1] = buf[m++];
      angmom[i][2] = buf[m++];
    }
  }


  for (k = 0; k < nstyles; k++)
    m += styles[k]->unpack_border_hybrid(n,first,&buf[m]);

  if (atom->nextra_border)
    for (int iextra = 0; iextra < atom->nextra_border; iextra++)
      m += modify->fix[atom->extra_border[iextra]]->
        unpack_border(n,first,&buf[m]);
}
