gck_password_get_module (GckPassword *self)
{
	g_return_val_if_fail (GCK_IS_PASSWORD (self), NULL);
	if (self->pv->for_token)
		return gck_slot_get_module (self->pv->token_or_key);
	else
		return gck_object_get_module (self->pv->token_or_key);
}
