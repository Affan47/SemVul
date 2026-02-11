free_tsin()
{
  free(current_tsin_fname); current_tsin_fname=NULL;

  if (fph) {
    fclose(fph); fph = NULL;
  }

  if (fp_phidx) {
    fclose(fp_phidx); fp_phidx=NULL;
  }
}
