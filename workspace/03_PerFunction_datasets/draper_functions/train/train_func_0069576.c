gdome_nl_item (GdomeNodeList *self, gulong index, GdomeException *exc)
{
	if (self == NULL) {
		*exc = GDOME_NULL_POINTER_ERR;
		return NULL;
	}
	if (((Gdome_xml_Node *)((Gdome_xml_NodeList *)self)->root)->n == NULL) {
		*exc = GDOME_INVALID_STATE_ERR;
		return NULL;
	}
	*exc = 0;
	return ((Gdome_xml_NodeList *)self)->vtab->item (self, index, exc);
}
