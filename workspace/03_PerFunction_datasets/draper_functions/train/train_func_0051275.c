quickselect_int_aux (int *set, int n, int k) {
  int x, elt;
  int lowcount = 0, eqcount = 1, j = 0, i;


  x = set[0];
  for (i = 1; i < n; i++) {
    if ((elt = set[i]) < x) {
      lowcount++;
    } else if (elt == x) {
      eqcount++;
    }
  }

  if (k <= lowcount) {
    for (i = 1; i < n; i++) {
      if (set[i] < x) {
	set[j++] = set[i];
      }
    }
    return quickselect_int_aux(set,j,k);

  } else if (k > lowcount+eqcount) {
    for (i = 1; i < n; i++) {
      if (set[i] > x) {
	set[j++] = set[i];
      }
    }
    return quickselect_int_aux(set,j,k-lowcount-eqcount);

  } else {
    return x;
  }
}
