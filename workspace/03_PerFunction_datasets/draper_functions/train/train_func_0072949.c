_startElement (void * userData, const gchar * name, const gchar ** atts)
{
  UT_XML * pXML = reinterpret_cast<UT_XML *>(userData);


  static const gchar * ptr = 0;
  const gchar ** new_atts = atts;
  if (atts == 0) new_atts = &ptr;

  pXML->startElement (reinterpret_cast<const char *>(name), reinterpret_cast<const char **>(new_atts));
}
