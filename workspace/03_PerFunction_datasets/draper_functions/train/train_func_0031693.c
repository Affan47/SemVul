stp_xml_init(void)
{
  stp_deprintf(STP_DBG_XML, "stp_xml_init: entering at level %d\n",
	       xml_is_initialised);
  if (xml_is_initialised >= 1)
    {
      xml_is_initialised++;
      return;
    }


#ifdef HAVE_LOCALE_H
  saved_locale = stp_strdup(setlocale(LC_ALL, NULL));
  stp_deprintf(STP_DBG_XML, "stp_xml_init: saving locale %s\n", saved_locale);
  setlocale(LC_ALL, "C");
#endif

  xml_is_initialised = 1;
}
