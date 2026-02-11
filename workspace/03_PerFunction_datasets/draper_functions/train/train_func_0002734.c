content_start (GsfXMLIn *xin, xmlChar const **attrs)
{
	SheetObject *so = gnm_xml_in_cur_obj (xin);
	SheetObjectImage *soi = SHEET_OBJECT_IMAGE (so);
	char const *image_type = NULL, *image_name = NULL;

	for (; attrs != NULL && attrs[0] && attrs[1] ; attrs += 2)
		if (attr_eq (attrs[0], "image-type"))
			image_type = CXML2C (attrs[1]);
	else if (attr_eq (attrs[0], "name"))
			image_name = CXML2C (attrs[1]);

	soi->type = g_strdup (image_type);
	if (image_name)
		soi->name = g_strdup (image_name);
}
