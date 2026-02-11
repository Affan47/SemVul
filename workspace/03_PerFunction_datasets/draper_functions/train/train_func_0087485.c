cattle_instruction_set_next (CattleInstruction *self,
                             CattleInstruction *next)
{
	g_return_if_fail (CATTLE_IS_INSTRUCTION (self));
	g_return_if_fail (next == NULL || CATTLE_IS_INSTRUCTION (next));
	g_return_if_fail (!self->priv->disposed);


	if (self->priv->next != NULL) {
		g_object_unref (self->priv->next);
	}


	self->priv->next = next;
	if (self->priv->next != NULL) {
		g_object_ref (self->priv->next);
	}
}
