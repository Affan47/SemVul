GRSTgaclPermFromChar(char *s)


{
  GRSTgaclPerm i;

  for (i=0; grst_perm_syms[i] != NULL; ++i)
       if (strcasecmp(grst_perm_syms[i], s) == 0) return grst_perm_vals[i];

  return -1;
}
