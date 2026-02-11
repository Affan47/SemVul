gr2lev (gadouble *vals, gadouble gr) {
gaint i;
  if (gr<1.0) return ( *(vals+1) + (1.0-gr)*(*(vals+1)-*(vals+2)) );
  if (gr>*vals) {
    i = (gaint)(*vals+0.1);
    return ( *(vals+i) + (gr-*vals)*(*(vals+i)-*(vals+i-1)) );
  }
  i = (gaint)gr;
  return (*(vals+i)+((gr-(gadouble)i)*(*(vals+i+1)-*(vals+i))));
}
