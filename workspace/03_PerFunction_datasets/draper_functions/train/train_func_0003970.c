dmix_extra_init(dirichlet_mix *m) {
  int i;
  XMALLOC(m->log_weights, m->comp_num);
  XMALLOC(m->scratch, m->comp_num);
  XMALLOC(m->counts, m->components->dim);
  XMALLOC(m->offsets, m->components->dim);
  for (i = 0; i < m->comp_num; ++i)
    m->log_weights[i] = xlog(m->weights[i]);
}
