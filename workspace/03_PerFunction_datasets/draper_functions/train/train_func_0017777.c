store_z_ucs_output_in_history(OUTPUTHISTORY *h, z_ucs *z_ucs_output)
{
  size_t len;
#ifdef ENABLE_TRACING
  z_ucs *cl;
#endif

  if (z_ucs_output == NULL)
    return;

  if ((len = z_ucs_len(z_ucs_output)) == 0)
    return;

  store_data_in_history(h, z_ucs_output, len, true);

#ifdef ENABLE_TRACING
  cl = get_current_line(h);
  TRACE_LOG("currentline:|");
  if (cl != NULL)
  {
    TRACE_LOG_Z_UCS(cl);
    free(cl);
  }
  TRACE_LOG("|line end.\n");
#endif
}
