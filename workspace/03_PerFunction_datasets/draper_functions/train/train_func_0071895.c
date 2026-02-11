ReferenceFilename() const
{
  const char* ref = gd_reference(D, NULL);

  if (ref == NULL)
    return NULL;

  return gd_raw_filename(D, ref);
}
