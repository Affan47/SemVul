input_header (FILE *fp, T this) {
  char *p;
  size_t length;

  if (feof(fp)) {
    return NULL;
  } else if (fgets(&(Header[0]),HEADERLEN,fp) == NULL) {

    return NULL;
  }

  if (Header[0] == '\n') {
    Header[0] = '\0';
  } else if ((p = rindex(&(Header[0]),'\n')) != NULL) {
    if (p[-1] == '\r') {
      p--;
    }
    *p = '\0';
  } else {

    while (fgets(&(Discard[0]),DISCARDLEN,fp) != NULL &&
	   rindex(&(Discard[0]),'\n') == NULL) ;
  }

  p = &(Header[0]);
  while (*p != '\0' && !isspace((int) *p)) {
    p++;
  }
  if (*p == '\0') {

    length = (p - &(Header[0]))/sizeof(char);
    this->acc = (char *) CALLOC_IN(length+1,sizeof(char));
    strcpy(this->acc,Header);
    this->restofheader = (char *) CALLOC_IN(1,sizeof(char));
    this->restofheader[0] = '\0';
  } else {
    *p = '\0';
    length = (p - &(Header[0]))/sizeof(char);
    this->acc = (char *) CALLOC_IN(length+1,sizeof(char));
    strcpy(this->acc,Header);
    p++;
    this->restofheader = (char *) CALLOC_IN(strlen(p)+1,sizeof(char));
    strcpy(this->restofheader,p);
  }

  return this->acc;
}
