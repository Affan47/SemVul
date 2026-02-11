add_att (test, varid, iatt)
     struct netcdf *test;
     int varid;
     struct cdfatt *iatt;
{
    static char pname[] = "add_att";
    int ia;

    if (test->natts >= MAX_TEST_ATTS) {
	(void)fprintf(stderr,
		      "%s: too many attributes (%d)", pname, test->natts);
	return;
    }


    for (ia = 0; ia < test->natts ; ia++) {
	if (test->atts[ia].var == varid &&
	    strcmp(test->atts[ia].name, iatt->name) == 0) {
	    test->atts[ia].type = iatt->type;
	    test->atts[ia].len = iatt->len;
	    test->atts[ia].val = iatt->val;
	    return;
	}
    }

    test->atts[test->natts].var = varid;
    test->atts[test->natts].name = (char *) emalloc(strlen(iatt->name) + 1);
    (void) strcpy(test->atts[test->natts].name, iatt->name);
    test->atts[test->natts].type = iatt->type;
    test->atts[test->natts].len = iatt->len;
    test->atts[test->natts].val = iatt->val;
    test->natts++;
    if (varid == NC_GLOBAL)
      test->ngatts++;
    else
      test->vars[varid].natts++;
}
