undcol (gaint i, gaint j) {
gadouble *p1, *p2, *p3, *p4;
char *p1u, *p2u, *p3u, *p4u;

  if (i<2 || i>imax-1 || j<2 || j>jmax-1) {
    printf ("Logic error 32 in gxshad\n");
    return (9);
  }
  p1 = gr + ((j-2)*imax+i-2);
  p2 = p1 + 2;
  p3 = p2 + imax*2;
  p4 = p3 - 2;

  p1u = gru + ((j-2)*imax+i-2);
  p2u = p1u + 2;
  p3u = p2u + imax*2;
  p4u = p3u - 2;


  if (*p1u==0 && *p3u==0 && *p2u!=0 && *p4u!=0) return(1);
  if (*p1u!=0 && *p3u!=0 && *p2u==0 && *p4u==0) return(2);
  printf ("Logic error 36 in gxshad\n");
  return (9);
}
