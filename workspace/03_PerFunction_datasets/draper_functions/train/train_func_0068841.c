output_string_stream (struct lto_output_stream *stream, const char *string)
{
  bool flag = false;

  if (string != NULL)
    {
      const size_t length = strlen (string);

      flag = true;
      output_data_stream (stream, &flag, sizeof (flag));
      output_data_stream (stream, &length, sizeof (length));
      output_data_stream (stream, string, length);
    }
  else
    output_data_stream (stream, &flag, sizeof (flag));
}
