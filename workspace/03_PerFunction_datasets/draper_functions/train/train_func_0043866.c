acs_emit_access_error(FILE *fp, int code, char *mesg)
{
  char *code_str;
  Common_status status;

  if (!test_emit_xml_format()) {
	if (mesg != NULL)
	  fprintf(fp, "799 Access error -- %s\n", mesg);
	else
	  fprintf(fp, "799 Access error\n");
	return(0);
  }

  emit_content_type_header = 0;
  emit_xml_header(fp, "dacs_acs");

  fprintf(fp, "<%s %s>\n",
		  make_xml_root_element("dacs_acs"), make_dacs_acs_attr_string());
  code_str = ds_xprintf("%d", code);
  init_common_status(&status, NULL, code_str, mesg);
  fprintf(fp, "%s", make_xml_common_status(&status));
  fprintf(fp, "</dacs_acs>\n");

  return(0);
}
