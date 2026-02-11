hdf_write_string (HDF *hdf, char **s)
{
  STRING str;
  NEOERR *err;

  *s = NULL;

  string_init (&str);

  err = hdf_dump_str (hdf, NULL, 1, &str);
  if (err)
  {
    string_clear (&str);
    return nerr_pass(err);
  }
  if (str.buf == NULL)
  {
    *s = strdup("");
    if (*s == NULL) return nerr_raise(NERR_NOMEM, "Unable to allocate empty string");
  }
  else
  {
    *s = str.buf;
  }

  return STATUS_OK;
}
