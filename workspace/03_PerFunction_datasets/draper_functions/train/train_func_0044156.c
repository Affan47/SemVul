file_handle_get_size (FileHandle *fh,
		      goffset *size)
{
  GFileInfo *info;
  gboolean res;

  if (fh->stream == NULL)
    return FALSE;

  info = NULL;
  if (fh->op == FILE_OP_READ)
    info = g_file_input_stream_query_info (fh->stream,
					   G_FILE_ATTRIBUTE_STANDARD_SIZE,
					   NULL, NULL);
  else if (fh->op == FILE_OP_WRITE)
    info = g_file_output_stream_query_info (fh->stream,
					    G_FILE_ATTRIBUTE_STANDARD_SIZE,
					    NULL, NULL);

  res = FALSE;
  if (info)
    {
      if (g_file_info_has_attribute (info, G_FILE_ATTRIBUTE_STANDARD_SIZE))
	{
	  *size = g_file_info_get_size (info);
	  res = TRUE;
	}
      g_object_unref (info);
    }
  return res;
}
