rx_cw_init(int n_samples)
{

  bb_buf_re = malloc(n_samples * sizeof(float));
  if (!bb_buf_re) {
    fprintf(stderr, "error allocating bb_buf_re\n");
    exit(-1);
  }

  bb_buf_im = malloc(n_samples * sizeof(float));
  if (!bb_buf_im) {
    fprintf(stderr, "error allocating bb_buf_im\n");
    exit(-1);
  }
}
