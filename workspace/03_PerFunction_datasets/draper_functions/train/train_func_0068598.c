pack_exchange(int i, double *buf)
{
  int k,m;

  int tmp = atom->nextra_grow;
  atom->nextra_grow = 0;

  m = 0;
  for (k = 0; k < nstyles; k++)
    m += styles[k]->pack_exchange(i,&buf[m]);

  atom->nextra_grow = tmp;

  if (atom->nextra_grow)
    for (int iextra = 0; iextra < atom->nextra_grow; iextra++)
      m += modify->fix[atom->extra_grow[iextra]]->pack_exchange(i,&buf[m]);

  buf[0] = m;
  return m;
}
