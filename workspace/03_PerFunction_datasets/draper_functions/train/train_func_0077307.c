find_timestamp (GstBuffer ** buffer, guint group, guint idx, HeaderData * data)
{
  data->timestamp = GST_BUFFER_TIMESTAMP (*buffer);
  data->offset = GST_BUFFER_OFFSET (*buffer);


  if (data->timestamp != -1)
    return GST_BUFFER_LIST_END;
  else
    return GST_BUFFER_LIST_CONTINUE;
}
