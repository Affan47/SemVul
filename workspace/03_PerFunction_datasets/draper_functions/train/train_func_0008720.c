xlsx_write_predefined_fills (GsfXMLOut *xml)
{
	char const **f = pre_def_fills;

	while (*f != NULL) {
		gsf_xml_out_start_element (xml, "fill");
		gsf_xml_out_start_element (xml, "patternFill");
		gsf_xml_out_add_cstr_unchecked (xml, "patternType", *f++);
		gsf_xml_out_end_element (xml);
		gsf_xml_out_end_element (xml);
	}
}
