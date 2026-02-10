__gst_vasprintf (char **result, char const *format, va_list args)
{
  size_t length;

  *result = vasnprintf (NULL, &length, format, args);
  if (*result == NULL)
    return -1;

  return length;
}
