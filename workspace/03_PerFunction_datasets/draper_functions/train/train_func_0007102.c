gdome_cds_isSupported (GdomeCDATASection *self, GdomeDOMString *feature, GdomeDOMString *version, GdomeException *exc)
{
	if (self == NULL) {
		*exc = GDOME_NULL_POINTER_ERR;
		return FALSE;
	}
	if (((Gdome_xml_Node *)self)->n == NULL) {
		*exc = GDOME_INVALID_STATE_ERR;
		return FALSE;
	}
	*exc = 0;
	return ((Gdome_xml_CDATASection *)self)->vtab->super.super.super.isSupported ((GdomeNode *)self, feature, version, exc);
}
