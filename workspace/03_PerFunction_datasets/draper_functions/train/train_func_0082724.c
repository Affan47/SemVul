b_in_bounds(int *xy, int *max_y, int *constraints, int xypos,
		int suma, int sumb, int m, int n)
{

  if (sumb <= suma && xy[xypos] <= max_y[xypos])

    if (var_check_1(constraints, xy, 0, m+n-1) &&
	var_check_2(constraints, xy, 0, m+n-1))
      return 1;
    else
      return 0;
  else
    return 0;
}
