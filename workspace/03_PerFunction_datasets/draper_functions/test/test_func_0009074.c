add_dim (test, idim)
     struct netcdf *test;
     struct cdfdim *idim;
{
    static char pname[] = "add_dim";

    if (test->ndims >= H4_MAX_NC_DIMS) {
	(void)fprintf(stderr,
		      "%s: too many dimensions (%d)", pname, test->ndims);
	return;
    }
    test->dims[test->ndims].size = idim->size;
    test->dims[test->ndims].name = (char *) emalloc(strlen(idim->name) + 1);
    (void) strcpy(test->dims[test->ndims].name, idim->name);
    if (idim->size == NC_UNLIMITED)
      test->xdimid = test->ndims;
    test->ndims++;
}
