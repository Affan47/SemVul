gdome_xml_di_createDocFromURI (GdomeDOMImplementation *self,
															 const char *uri,
															 unsigned int  mode,
															 GdomeException *exc) {
	int oldvalue =  xmlDoValidityCheckingDefaultValue;
	GdomeDocument *ret = NULL;
	int prevSubstValue;

	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (uri != NULL, NULL);
	g_return_val_if_fail (exc != NULL, NULL);
	g_assert(self == (GdomeDOMImplementation *)gdome_xml_DOMImplementation);

	if (mode & GDOME_LOAD_SUBSTITUTE_ENTITIES)
		prevSubstValue = xmlSubstituteEntitiesDefault (1);
	else
		prevSubstValue = xmlSubstituteEntitiesDefault (0);

	if (mode & GDOME_LOAD_COMPLETE_ATTRS)
		xmlLoadExtDtdDefaultValue |= XML_COMPLETE_ATTRS;

	switch (mode & (GDOME_LOAD_PARSING |
									GDOME_LOAD_VALIDATING |
									GDOME_LOAD_RECOVERING)) {
	case GDOME_LOAD_PARSING:
		xmlDoValidityCheckingDefaultValue = 0;
		ret = (GdomeDocument *)gdome_xml_n_mkref ((xmlNode *)xmlParseFile (uri));
		break;
	case GDOME_LOAD_VALIDATING:
		xmlDoValidityCheckingDefaultValue = 1;
		ret = (GdomeDocument *)gdome_xml_n_mkref ((xmlNode *)xmlParseFile (uri));
		break;
	case GDOME_LOAD_RECOVERING:
		xmlDoValidityCheckingDefaultValue = 0;
		ret = (GdomeDocument *)gdome_xml_n_mkref ((xmlNode *)xmlRecoverFile (uri));
		break;
	}

	xmlSubstituteEntitiesDefault (prevSubstValue);
	xmlDoValidityCheckingDefaultValue = oldvalue;
	return ret;
}
