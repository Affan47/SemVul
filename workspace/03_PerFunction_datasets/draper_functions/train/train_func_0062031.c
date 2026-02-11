folks_persona_store_get_can_alias_personas (FolksPersonaStore* self) {
	g_return_val_if_fail (self != NULL, 0);
	return FOLKS_PERSONA_STORE_GET_CLASS (self)->get_can_alias_personas (self);
}
