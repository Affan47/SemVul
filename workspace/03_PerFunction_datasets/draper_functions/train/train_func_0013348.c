fstring(
     nc_type type,
     void *valp,
     int num)
{
    static char *cp;
    signed char *schp;
    short *shortp;
    int *intp;
    float *floatp;
    double *doublep;

    switch (type) {
      case NC_BYTE:
	cp = (char *) emalloc (10);
	schp = (signed char *)valp;
        sprintf(cp,"%d", schp[num]);
	return cp;

      case NC_SHORT:
	cp = (char *) emalloc (10);
	shortp = (short *)valp;
	(void) sprintf(cp,"%d",* (shortp + num));
	return cp;

      case NC_INT:
	cp = (char *) emalloc (20);
	intp = (int *)valp;
	(void) sprintf(cp,"%d",* (intp + num));
	return cp;

      case NC_FLOAT:
	cp = (char *) emalloc (20);
	floatp = (float *)valp;
	(void) sprintf(cp,"%.8g",* (floatp + num));
	return cp;

      case NC_DOUBLE:
	cp = (char *) emalloc (25);
	doublep = (double *)valp;
	(void) sprintf(cp,"%.16g",* (doublep + num));
	expe2d(cp);
	return cp;

      default:
	derror("fstring: bad type code");
	return 0;
    }
}
