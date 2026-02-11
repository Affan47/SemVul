cmd_start_zip_out(struct ctrl_command *cmd)
{
#ifdef HAVE_LIBZ
  int ret;

  if (out_state.zip)
    send_error("can't start compression - already started!");

  out_state.zip_state.stream.total_in = 0;
  out_state.zip_state.stream.total_out = 0;
  out_state.zip_state.stream.zalloc = (alloc_func)0;
  out_state.zip_state.stream.zfree = (free_func)0;
  out_state.zip_state.stream.data_type = Z_ASCII;

  if (out_state.zip_state.level <= 0)
    out_state.zip_state.level = Z_DEFAULT_COMPRESSION;

  if ((ret = deflateInit(&out_state.zip_state.stream,
                         out_state.zip_state.level)) != Z_OK)
    send_error("deflateInit failed: %d (%s)", ret, zError(ret));

  out_state.zip = 1;
#else
  send_error("can't start compression - no libz support!");
#endif
}
