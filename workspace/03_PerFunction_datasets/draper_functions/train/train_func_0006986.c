vector_write_bin_ns(Vector *v, FILE *fp) {
  if (!v || !fp) {
    if (MATR_DEBUG_MODE) {
      fprintf(stderr, "vector_write: null arguments.\n");
    }
    return 0;
  }
  if (v->type != NON_SPARSE) {
    return vector_write_bin_fp(v, fp);
  }

  if (v->compact) {
    return sizeof(int)*fwrite(v->data.nsarray.compact, sizeof(int), v->dim, fp);
  }

  return sizeof(double)*fwrite(v->data.nsarray.precise, sizeof(double), v->dim,
			       fp);
}
