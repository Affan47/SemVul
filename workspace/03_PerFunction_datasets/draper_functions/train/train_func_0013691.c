gsl_sf_lnfact (const unsigned int n) {
  if (n <= GSL_SF_FACT_NMAX) {
    return log(fact_table[n].f);
  } else {
    return gsl_sf_lngamma(n+1.0);
  }
}
