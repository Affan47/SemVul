mpc_input_range(mpc_input_t *i, char c, char d, char **o) {
  char x = mpc_input_getc(i);
  if (mpc_input_terminated(i)) { return 0; }
  return x >= c && x <= d ? mpc_input_success(i, x, o) : mpc_input_failure(i, x);
}
