init_binomial_dp_tab(void)
{
  if (binomial_dp_tab == NULL) {
    unsigned long idx, jdx,
                  rows = GT_BINOMIAL_MAX_N_DP + 1UL,
                  cols = GT_DIV2(GT_BINOMIAL_MAX_N_DP) + 1;
    gt_array2dim_malloc(binomial_dp_tab, rows, cols);
    for (idx=0; idx < rows; idx++)
      for (jdx=0; jdx < cols; jdx++)
        binomial_dp_tab[idx][jdx] = UNDEFTABVALUE;
  }
}
