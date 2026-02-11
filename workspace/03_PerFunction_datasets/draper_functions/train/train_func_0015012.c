Chrsubset_print_chromosomes (T this, IIT_T chromosome_iit) {
  int i;
  bool firstp = true, allocp;
  char *label;

  for (i = 0; i < IIT_total_nintervals(chromosome_iit); i++) {
    if (this == NULL || this->includep[i] == true) {
      label = IIT_label(chromosome_iit,i+1,&allocp);
      if (firstp == true) {
	printf("%s",label);
	firstp = false;
      } else {
	printf(",%s",label);
      }
      if (allocp == true) {
	FREE(label);
      }
    }
  }

  return;
}
