ifoFree_PTL_MAIT(ifo_handle_t *ifofile) {
  unsigned int i;

  if(!ifofile)
    return;

  if(ifofile->ptl_mait) {
    for(i = 0; i < ifofile->ptl_mait->nr_of_countries; i++) {
      free(ifofile->ptl_mait->countries[i].pf_ptl_mai);
    }
    free(ifofile->ptl_mait->countries);
    free(ifofile->ptl_mait);
    ifofile->ptl_mait = NULL;
  }
}
