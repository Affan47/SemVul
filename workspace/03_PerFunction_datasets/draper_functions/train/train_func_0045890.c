zp2(
  DdManager * zdd,
  DdNode * f,
  st_table * t)
{
    DdNode	*n;
    int		T, E;
    DdNode	*base = DD_ONE(zdd);

    if (f == NULL)
	return(0);

    if (Cudd_IsConstant(f)) {
	(void)fprintf(zdd->out, "ID = %d\n", (f == base));
	return(1);
    }
    if (st_is_member(t, (char *)f) == 1)
	return(1);

    if (st_insert(t, (char *) f, NULL) == ST_OUT_OF_MEM)
	return(0);

#if SIZEOF_VOID_P == 8
    (void) fprintf(zdd->out, "ID = 0x%lx\tindex = %u\tr = %u\t",
	(ptruint)f / (ptruint) sizeof(DdNode), f->index, f->ref);
#else
    (void) fprintf(zdd->out, "ID = 0x%x\tindex = %hu\tr = %hu\t",
	(ptruint)f / (ptruint) sizeof(DdNode), f->index, f->ref);
#endif

    n = cuddT(f);
    if (Cudd_IsConstant(n)) {
	(void) fprintf(zdd->out, "T = %d\t\t", (n == base));
	T = 1;
    } else {
#if SIZEOF_VOID_P == 8
	(void) fprintf(zdd->out, "T = 0x%lx\t", (ptruint) n /
		       (ptruint) sizeof(DdNode));
#else
	(void) fprintf(zdd->out, "T = 0x%x\t", (ptruint) n /
		       (ptruint) sizeof(DdNode));
#endif
	T = 0;
    }

    n = cuddE(f);
    if (Cudd_IsConstant(n)) {
	(void) fprintf(zdd->out, "E = %d\n", (n == base));
	E = 1;
    } else {
#if SIZEOF_VOID_P == 8
	(void) fprintf(zdd->out, "E = 0x%lx\n", (ptruint) n /
		      (ptruint) sizeof(DdNode));
#else
	(void) fprintf(zdd->out, "E = 0x%x\n", (ptruint) n /
		       (ptruint) sizeof(DdNode));
#endif
	E = 0;
    }

    if (E == 0)
	if (zp2(zdd, cuddE(f), t) == 0) return(0);
    if (T == 0)
	if (zp2(zdd, cuddT(f), t) == 0) return(0);
    return(1);

}
