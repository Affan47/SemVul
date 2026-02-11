SST_AddDispersion(SST_Stats inst, double dispersion)
{
  int m, i;

  for (m = 0; m < inst->n_samples; m++) {
    i = get_buf_index(inst, m);
    inst->root_dispersions[i] += dispersion;
    inst->peer_dispersions[i] += dispersion;
  }
}
