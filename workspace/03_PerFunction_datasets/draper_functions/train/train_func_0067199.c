Shortread_print_oneline (FILE *fp, T this) {
  int i = 0;

  if (this->fulllength == 0 || isspace(this->contents[0])) {
    fprintf(fp,"(null)");
  } else {
    for (i = 0; i < this->fulllength; i++) {
      fprintf(fp,"%c",this->contents[i]);
    }
    for (i = 0; i < this->choplength; i++) {
      fprintf(fp,"%c",this->chop[i]);
    }
  }
  return;
}
