mono_type_hash (gconstpointer data)
{
	const MonoType *type = (const MonoType *) data;
	if (type->type == MONO_TYPE_GENERICINST)
		return mono_generic_class_hash (type->data.generic_class);
	else
		return type->type | (type->byref << 8) | (type->attrs << 9);
}
