gdome_n_ref (GdomeNode *self, GdomeException *exc)
{
	if (self == NULL) {
		*exc = GDOME_NULL_POINTER_ERR;
		return;
	}
	if (((Gdome_xml_Node *)self)->n == NULL) {
		*exc = GDOME_INVALID_STATE_ERR;
		return;
	}
	*exc = 0;
	((Gdome_xml_Node *)self)->vtab->ref (self, exc);
}
