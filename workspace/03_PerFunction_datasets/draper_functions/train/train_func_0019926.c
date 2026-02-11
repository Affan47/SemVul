Analyze_GetAmpEnv (el_nframes_t idx1,
					el_nframes_t idx2) {
  el_sample_t alen = (idx2-idx1)*d->numch;
  if (alen == 0)
    return 0.0;

  register el_sample_t amp = 0.0;
  for (int i = 0; i < d->numch; i++) {
    register el_sample_t *sbuf = sbufs[i];
    for (register el_nframes_t n = idx1; n < idx2; n++)
      amp += fabs(sbuf[n]);
  }

  return amp/alen;
}
