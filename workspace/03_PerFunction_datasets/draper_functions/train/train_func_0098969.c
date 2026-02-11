arg_type_xml_string (int t)
{
    if (t == GRETL_TYPE_SCALAR_REF) {
	return "scalarref";
    } else if (t == GRETL_TYPE_SERIES_REF) {
	return "seriesref";
    } else if (t == GRETL_TYPE_MATRIX_REF) {
	return "matrixref";
    } else if (t == GRETL_TYPE_BUNDLE_REF) {
	return "bundleref";
    } else {
	return gretl_arg_type_name(t);
    }
}
