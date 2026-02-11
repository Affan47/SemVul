nrgAddSaturate(const FIXP_DBL a, const FIXP_DBL b) {
  return ( (a>=(FIXP_DBL)MAXVAL_DBL-b) ? (FIXP_DBL)MAXVAL_DBL : (a + b) );
}
