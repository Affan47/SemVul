cattle_instruction_set_value (CattleInstruction      *self,
                              CattleInstructionValue  value)
{
	gpointer enum_class;
	GEnumValue *enum_value;

	g_return_if_fail (CATTLE_IS_INSTRUCTION (self));
	g_return_if_fail (!self->priv->disposed);


	enum_class = g_type_class_ref (CATTLE_TYPE_INSTRUCTION_VALUE);
	enum_value = g_enum_get_value (enum_class, value);
	g_type_class_unref (enum_class);
	g_return_if_fail (enum_value != NULL);

	self->priv->value = value;
}
