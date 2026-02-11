cint(char *s, long int *nerr) {
  long int v;
  char *endptr;
  *nerr = 0;
  v = strtol(s, &endptr, BASE_TEN);

#ifdef __UNIT_TESTING_DEBUG__
  fprintf(stderr, "v: %12d %4d %4d <%-12s> <%12s>\n",
	  v, errno, strlen(endptr), endptr, s);
#endif


  if(endptr == s)          { *nerr = CONVERSION_NOT_NUMERIC;       }
  else if(*endptr != '\0') { *nerr = CONVERSION_EXTRA_CHARACTERS;  }
  else if(errno == EINVAL) { *nerr = CONVERSION_NOT_CONVERTED;     }
  else if(errno == ERANGE) {
    if(v == LONG_MIN) { *nerr = CONVERSION_TOO_SMALL;  }
    if(v == LONG_MAX) { *nerr = CONVERSION_TOO_LARGE;  }
  }
  errno = 0;
  return v;
}
