find_best_ref(double *displs, int which_crystal,
                                 double &xi_sq, double *dxi)
{
  int i;
  double dot,tmp;

  double  best_dot  = -1.0;
  int     best_i    = -1;
  int     best_sign = 0;

  for (i = 0; i < half_fcc_nn; i++) {
    dot = displs[0] * half_xi_chi_vec[which_crystal][i][0] +
      displs[1] * half_xi_chi_vec[which_crystal][i][1] +
      displs[2] * half_xi_chi_vec[which_crystal][i][2];
    if (fabs(dot) > best_dot) {
      best_dot = fabs(dot);
      best_i = i;
      if (dot < 0.0) best_sign = -1;
      else best_sign = 1;
    }
  }

  xi_sq = 0.0;
  for (i = 0; i < 3; i++) {
    tmp = displs[i] - best_sign * half_xi_chi_vec[which_crystal][best_i][i];
    xi_sq += tmp*tmp;
  }

  if (xi_sq > 0.0) {
    double xi = sqrt(xi_sq);
    for (i = 0; i < 3; i++)
      dxi[i] = (best_sign * half_xi_chi_vec[which_crystal][best_i][i] -
                displs[i]) / xi;
  } else dxi[0] = dxi[1] = dxi[2] = 0.0;
}
