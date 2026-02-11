inf_from_stream(fz_FILE * stream, datafilename_fn_t datafn)
{
  struct inputfile *inf;

  fc_assert_ret_val(NULL != stream, NULL);
  inf = fc_malloc(sizeof(*inf));
  init_zeros(inf);

  inf->filename = NULL;
  inf->fp = stream;
  inf->datafn = datafn;

  log_debug("inputfile: opened \"%s\" ok", inf_filename(inf));
  return inf;
}
