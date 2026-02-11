main ()
{
  uint_t win_s = 1024;
  uint_t n_filters = 13;

  cvec_t *in_spec = new_cvec (win_s);
  fvec_t *out_filters = new_fvec (n_filters);


  aubio_filterbank_t *o = new_aubio_filterbank (n_filters, win_s);


  uint_t n = 10;
  while (n) {
    aubio_filterbank_do (o, in_spec, out_filters);
    n--;
  }


  fmat_t *coeffs;
  coeffs = aubio_filterbank_get_coeffs (o);
  fmat_print (coeffs);

  aubio_filterbank_set_coeffs (o, coeffs);
  coeffs = aubio_filterbank_get_coeffs (o);
  fmat_print (coeffs);


  del_aubio_filterbank (o);
  del_cvec (in_spec);
  del_fvec (out_filters);
  aubio_cleanup ();

  return 0;
}
