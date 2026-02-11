parse_value(const fileinfo *cfile, const batinfo_field *field) {
  if (*field->valuep != VAL_NOTFOUND)
    return batfailf("value specified multiple times");

  if (!field->enumarray[0]) {

    char *ep;
    *field->valuep= strtoull(batlinevalue,&ep,10);
    if (*ep)
      batfailf("value number syntax incorrect");

  } else {

    const char *const *enumsearch;
    for (*field->valuep=0, enumsearch=field->enumarray;
	 *enumsearch && strcmp(*enumsearch,batlinevalue);
	 (*field->valuep)++, enumsearch++);
    if (!*enumsearch)
      batfailf("unknown enum value");

  }
  return 0;
}
