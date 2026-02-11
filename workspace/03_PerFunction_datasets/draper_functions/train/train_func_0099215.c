input_data_mixed_double (const guint8 * _in, gfloat * out, guint len,
    guint channels, gfloat max_value, guint op, guint nfft)
{
  guint i, j, ip = 0;
  gfloat v;
  gdouble *in = (gdouble *) _in;

  for (j = 0; j < len; j++) {
    v = in[ip++];
    for (i = 1; i < channels; i++)
      v += in[ip++];
    out[op] = v / channels;
    op = (op + 1) % nfft;
  }
}
