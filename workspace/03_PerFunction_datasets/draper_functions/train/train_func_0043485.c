cmor_attribute_in_list(char *name, int n, char (*atts)[CMOR_MAX_STRING]) {
  int i,found=1;

  for (i=0;i<n;i++) {
    if (strcmp(name,atts[i])==0) found=0;
  }
  return found;
}
