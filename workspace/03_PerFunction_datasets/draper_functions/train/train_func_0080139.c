next_combo_ss(int length, int basis[MAX_BASIS][MAX_COEF],
		  int num_basis, int constraints[MAX_COEF],
		  int combo[MAX_BASIS], int sum[MAX_COEF],
		  int start_flag,
		  int combos[MAX_COMBOS][MAX_BASIS],
		  int *np,
		  int ss_parm)
{
  int i, go, ok;

  if (start_flag) {
    *np = 0;
    go = next_combo_a(length,basis,num_basis,constraints,combo,sum,1);
    while (go) {
      for (i=0, ok = 1; i < *np && ok; i++)


	if (superset_degree(combo, combos[i], num_basis) > ss_parm)
	  ok = 0;

      if (ok) {
	if (*np == MAX_COMBOS) {
	  printf("next_combo_ss: MAX_COMBOS.\n");
	  go = 0;
	}
	else {
	  for (i=0; i<num_basis; i++)
	    combos[*np][i] = combo[i];
	  (*np)++;
	}
      }

      if (go)
	go = next_combo_a(length,basis,num_basis,constraints,combo,sum,0);
    }
  }

  if (*np > 0) {
    (*np)--;
    for (i=0; i<num_basis; i++)
      combo[i] = combos[*np][i];
    return 1;
  }
  else
    return 0;

}
