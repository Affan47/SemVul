gdome_xmlIsNsDecl (xmlAttr *a) {
	if (xmlStrEqual(a->name, "xmlns"))
		return 1;
	if (a->ns != NULL)
		if (xmlStrEqual(a->ns->href, GDOME_XMLNS_NAMESPACE))
			return 1;
	return 0;
}
