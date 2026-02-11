_ds_compute_sparse(const char *token) {
  int sparse = 0, i;

  if (!strncmp(token, "#+", 2))
    sparse++;
  if (strlen(token)>=2 && !strncmp((token+strlen(token))-2, "+#", 2))
    sparse++;
  for(i=0;token[i];i++) {
    if (!strncmp(token+i, "+#+", 3)) {
      sparse++;
      i++;
    }
  }

  return sparse;
}
