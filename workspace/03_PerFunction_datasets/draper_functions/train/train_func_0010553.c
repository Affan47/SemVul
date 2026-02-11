perform_svd(gsl_matrix * a, gsl_matrix * v, gsl_vector * s) {

  gint status;
  gsl_vector * w;

  w = gsl_vector_alloc(s->size);
  g_return_val_if_fail(w != NULL, -1);

  status = gsl_linalg_SV_decomp(a, v, s, w);
  gsl_vector_free(w);

  return status;
}
