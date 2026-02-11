del_att (test, varid, iatt)
     struct netcdf *test;
     int varid;
     struct cdfatt *iatt;
{
    static char pname[] = "del_att";
    int ia, ib;

    for (ia = 0; ia < test->natts ; ia++) {
	if (test->atts[ia].var == varid &&
	    strcmp(test->atts[ia].name, iatt->name) == 0) {
	    Free(test->atts[ia].name);
            for (ib = ia+1; ib < test->natts; ib++) {
		test->atts[ib-1].var =   test->atts[ib].var;
		test->atts[ib-1].name =  test->atts[ib].name;
		test->atts[ib-1].type =  test->atts[ib].type;
		test->atts[ib-1].len =   test->atts[ib].len;
		test->atts[ib-1].val =   test->atts[ib].val;
	    }
	    test->natts--;
	    if (varid == NC_GLOBAL)
	      test->ngatts--;
	    else
	      test->vars[varid].natts--;
	    return;
	}
    }

    (void) fprintf(stderr, "%s: no such attribute as (%s, %s)", pname,
		   test->vars[varid].name, iatt->name);
}
