nextMatrix (dReal *A, int n, int m, int lower_tri,
				     const char *name, ...)
{
  if (A==0 || n < 1 || m < 1 || name==0) dDebug (0,"bad args to nextMatrix");
  int num = n*dPAD(m);

  if (afterfirst==0) {
    dMatInfo *mi = (dMatInfo*) dAlloc (sizeof(dMatInfo));
    mi->n = n;
    mi->m = m;
    mi->size = num * sizeof(dReal);
    mi->data = (dReal*) dAlloc (mi->size);
    memcpy (mi->data,A,mi->size);

    va_list ap;
    va_start (ap,name);
    vsprintf (mi->name,name,ap);
    if (strlen(mi->name) >= sizeof (mi->name)) dDebug (0,"name too long");

    mat.push (mi);
    return 0;
  }
  else {
    if (lower_tri && n != m)
      dDebug (0,"dMatrixComparison, lower triangular matrix must be square");
    if (index >= mat.size()) dDebug (0,"dMatrixComparison, too many matrices");
    dMatInfo *mp = mat[index];
    index++;

    dMatInfo mi;
    va_list ap;
    va_start (ap,name);
    vsprintf (mi.name,name,ap);
    if (strlen(mi.name) >= sizeof (mi.name)) dDebug (0,"name too long");

    if (strcmp(mp->name,mi.name) != 0)
      dDebug (0,"dMatrixComparison, name mismatch (\"%s\" and \"%s\")",
	      mp->name,mi.name);
    if (mp->n != n || mp->m != m)
      dDebug (0,"dMatrixComparison, size mismatch (%dx%d and %dx%d)",
	      mp->n,mp->m,n,m);

    dReal maxdiff;
    if (lower_tri) {
      maxdiff = dMaxDifferenceLowerTriangle (A,mp->data,n);
    }
    else {
      maxdiff = dMaxDifference (A,mp->data,n,m);
    }
    if (maxdiff > tol)
      dDebug (0,"dMatrixComparison, matrix error (size=%dx%d, name=\"%s\", "
	      "error=%.4e)",n,m,mi.name,maxdiff);
    return maxdiff;
  }
}
