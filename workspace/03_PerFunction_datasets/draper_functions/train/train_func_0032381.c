get_CI_energy(int nSOs,
			int nEl,
			const four_idx_SO_struct* g_SO,
			const two_idx_SO_struct* h_SO,
			int nSlaterDets,
			const SlaterDet_struct* SlaterDetList,
			const ergo_real* coeffList,
			ergo_real nuclearEnergy)
{
  two_idx_SO_struct* D = new two_idx_SO_struct;
  four_idx_SO_struct* d = new four_idx_SO_struct;

  get_1e_density_matrix(nSOs,
			nEl,
			D,
			nSlaterDets,
			SlaterDetList,
			coeffList);

  get_2e_density_matrix(nSOs,
			nEl,
			d,
			nSlaterDets,
			SlaterDetList,
			coeffList);

  int p, q, r, s;

  ergo_real energy_1el = 0;
  for(p = 0; p < nSOs; p++)
    for(q = 0; q < nSOs; q++)
      energy_1el += D->x[p][q] * h_SO->x[p][q];

  ergo_real energy_2el = 0;
  for(p = 0; p < nSOs; p++)
    for(q = 0; q < nSOs; q++)
      for(r = 0; r < nSOs; r++)
	for(s = 0; s < nSOs; s++)
	  energy_2el += 0.5 * d->x[p][q][r][s] * g_SO->x[p][q][r][s];

  delete D;
  delete d;

  return energy_1el + energy_2el + nuclearEnergy;
}
