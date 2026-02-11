oo_attr_percent_or_distance (GsfXMLIn *xin, xmlChar const * const *attrs,
			     int ns_id, char const *name, gnm_float *res,
			     gboolean *found_percent)
{
	char *end;
	double tmp;

	g_return_val_if_fail (attrs != NULL, FALSE);
	g_return_val_if_fail (attrs[0] != NULL, FALSE);
	g_return_val_if_fail (attrs[1] != NULL, FALSE);
	g_return_val_if_fail (res != NULL, FALSE);
	g_return_val_if_fail (found_percent != NULL, FALSE);

	if (!gsf_xml_in_namecmp (xin, CXML2C (attrs[0]), ns_id, name))
		return FALSE;

	tmp = gnm_strto (CXML2C (attrs[1]), &end);
	if (*end != '%' || *(end + 1)) {
		*found_percent = FALSE;
		return (NULL != oo_parse_distance (xin, attrs[1], name, res));
	}
	*res = tmp/100.;
	*found_percent = TRUE;
	return TRUE;
}
