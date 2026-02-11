print_splicesite_labels (FILE *fp, T this, int typeint, int chimera_pos, char *tag) {
  Genomicpos_T splicesitepos;
  int *splicesites, nsplicesites, i;
  char *label;
  bool allocp;

  if (this->plusp == true) {
    splicesitepos = this->genomicstart - this->chroffset + chimera_pos;
  } else {
    splicesitepos = this->genomicstart - this->chroffset - chimera_pos;
  }


  if (this->chimera_knownp == true) {

    splicesites = IIT_get_exact_multiple_with_divno(&nsplicesites,splicesites_iit,
						    splicesites_divint_crosstable[this->chrnum],
						    splicesitepos,splicesitepos+1U,typeint);
    if (nsplicesites == 0) {
#if 0

      fprintf(stderr,"Supposed to have a splicesite at chrnum %d, %u..%u, type %d\n",
	      this->chrnum,splicesitepos,splicesitepos+1U,typeint);
#endif
    } else {
      fprintf(fp,",%s:",tag);
      label = IIT_label(splicesites_iit,splicesites[0],&allocp);
      fprintf(fp,"%s",label);
      if (allocp) FREE(label);

      for (i = 1; i < nsplicesites; i++) {
	label = IIT_label(splicesites_iit,splicesites[i],&allocp);
	fprintf(fp,"|%s",label);
	if (allocp) FREE(label);
      }
      FREE(splicesites);
    }
  }

  return;
}
