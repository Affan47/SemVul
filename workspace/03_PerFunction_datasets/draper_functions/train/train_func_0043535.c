list_init_thermo_energy(int mask, int &n, int *&list)
{
  delete [] list;

  n = 0;
  for (int i = 0; i < nfix; i++)
    if (fmask[i] & mask && fix[i]->thermo_energy) n++;
  list = new int[n];

  n = 0;
  for (int i = 0; i < nfix; i++)
    if (fmask[i] & mask && fix[i]->thermo_energy) list[n++] = i;
}
