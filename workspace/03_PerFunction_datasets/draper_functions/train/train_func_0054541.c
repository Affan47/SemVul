cmor_copy_data(double **dest1, void *data, char type, int nelts) {
  int i;
  char msg[CMOR_MAX_STRING];
  double *dest;

  cmor_add_traceback("cmor_copy_data");
  dest = *dest1;

  if (dest !=NULL) {
    free(dest);
  }

  dest = malloc(nelts*sizeof(double));

  for (i=0;i<nelts;i++) {
    if (type=='f') dest[i] = (double)((float *)data)[i];
    else if (type=='i') dest[i] = (double)((int *)data)[i];
    else if (type=='l') dest[i] = (double)((long *)data)[i];
    else if (type=='d') dest[i] = (double)((double *)data)[i];
    else {
      snprintf(msg,CMOR_MAX_STRING,"wrong data type: %c",type);
      cmor_handle_error(msg,CMOR_CRITICAL);
    }
  }
  *dest1=dest;
  cmor_pop_traceback();
  return 0;
}
