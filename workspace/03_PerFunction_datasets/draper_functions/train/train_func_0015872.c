print_bibtex (void *cls,
	      const char *plugin_name,
	      enum EXTRACTOR_MetaType type,
	      enum EXTRACTOR_MetaFormat format,
	      const char *data_mime_type,
	      const char *data,
	      size_t data_len)
{
  unsigned int i;

  if (YES != print[type])
    return 0;
  if (EXTRACTOR_METAFORMAT_UTF8 != format)
    return 0;
  if (EXTRACTOR_METATYPE_BIBTEX_ENTRY_TYPE == type)
    {
      entry_type = strdup (data);
      return 0;
    }
  for (i = 0; NULL != btm[i].bibTexName; i++)
    if ( (NULL == btm[i].value) &&
	 (btm[i].le_type == type) )
      btm[i].value = strdup (data);
  return 0;
}
