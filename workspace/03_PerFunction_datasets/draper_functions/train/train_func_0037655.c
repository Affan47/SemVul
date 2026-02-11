input_header (bool *filterp, char **restofheader, FILE *fp) {
  char *acc = NULL, *p, *q;
  size_t length;

  *filterp = false;

  if (feof(fp)) {
    return (char *) NULL;
  } else if (fgets(&(Header[0]),HEADERLEN,fp) == NULL) {

    return (char *) NULL;
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

  if (filter_chastity_p == true) {
    q = p;

    while (*q != '\0' && *q != ':') {
      q++;
    }
    if (*q != '\0') {
      q++;
      if (*q == 'Y') {
	*filterp = true;
      }
    }
  }

  if (*p == '\0') {

    length = (p - &(Header[0]))/sizeof(char);
    acc = (char *) CALLOC_IN(length+1,sizeof(char));
    strcpy(acc,Header);
    (*restofheader) = (char *) CALLOC_IN(1,sizeof(char));
    (*restofheader)[0] = '\0';
  } else {
    *p = '\0';
    length = (p - &(Header[0]))/sizeof(char);
    acc = (char *) CALLOC_IN(length+1,sizeof(char));
    strcpy(acc,Header);
    p++;
    *restofheader = (char *) CALLOC_IN(strlen(p)+1,sizeof(char));
    strcpy(*restofheader,p);
  }

  return acc;
}
