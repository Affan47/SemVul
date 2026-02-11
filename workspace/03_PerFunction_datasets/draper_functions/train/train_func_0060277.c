gdome_n_canAppend (GdomeNode *self, GdomeNode *newChild, GdomeException *exc)
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
	return ((Gdome_xml_Node *)self)->vtab->canAppend (self, newChild, exc);
}
