send_request_sync (GOutputStream     *output,
                   DsiCommand        command,
                   guint16           request_id,
                   guint32           writeOffset,
                   gsize             len,
                   const char        *data,
                   GCancellable      *cancellable,
                   GError            **error)
{
  DSIHeader dsi_header;
  gboolean res;
  gsize write_count, bytes_written;

  dsi_header.flags = 0x00;
  dsi_header.command = command;
  dsi_header.requestID = GUINT16_TO_BE (request_id);
  dsi_header.writeOffset = GUINT32_TO_BE (writeOffset);
  dsi_header.totalDataLength = GUINT32_TO_BE (len);
  dsi_header.reserved = 0;

  write_count = sizeof (DSIHeader);
  res = g_output_stream_write_all (output, &dsi_header, write_count,
                                   &bytes_written, cancellable, error);
  if (!res)
    return FALSE;

  if (data == NULL)
    return TRUE;

  write_count = len;
  res = g_output_stream_write_all (output, data, write_count, &bytes_written,
                                   cancellable, error);
  if (!res)
    return FALSE;

  return TRUE;
}
