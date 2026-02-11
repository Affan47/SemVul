fsp_stat_filename (gftp_request * request, const char *filename,
                   mode_t * mode, off_t * filesize)
{
  fsp_protocol_data * lpd;
  struct stat st;

  g_return_val_if_fail (request != NULL, GFTP_EFATAL);
  g_return_val_if_fail (request->protonum == GFTP_FSP_NUM, GFTP_EFATAL);
  g_return_val_if_fail (filename != NULL, GFTP_EFATAL);

  lpd = request->protocol_data;
  g_return_val_if_fail (lpd->fsp != NULL, GFTP_EFATAL);

  if (fsp_stat (lpd->fsp,filename, &st) != 0)
    return (GFTP_ERETRYABLE);

  *mode = st.st_mode;
  *filesize = st.st_size;

  return (0);
}
