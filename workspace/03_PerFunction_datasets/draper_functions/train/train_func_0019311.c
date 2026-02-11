srunner_open_xmlfile (SRunner *sr)
{
  FILE *f = NULL;
  if (srunner_has_xml (sr)) {
    f = fopen(srunner_xml_fname(sr), "w");
    if (f == NULL)
      eprintf ("Error in call to fopen while opening xml file %s:", __FILE__, __LINE__ - 2,
	       sr->xml_fname);
  }
  return f;
}
