gdome_xml_di_mkref (void) {
	if (gdome_xml_DOMImplementation == NULL) {
		gdome_xml_DOMImplementation = g_new (Gdome_xml_DOMImplementation, 1);
		memset(gdome_xml_DOMImplementation, 0, sizeof(Gdome_xml_DOMImplementation));
		gdome_xml_DOMImplementation->refcnt = 1;
		gdome_xml_DOMImplementation->vtab = &gdome_xml_di_vtab;
	} else
		gdome_xml_DOMImplementation->refcnt++;

	return (GdomeDOMImplementation *)gdome_xml_DOMImplementation;
}
