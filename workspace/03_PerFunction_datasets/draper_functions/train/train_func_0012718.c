ves_icall_System_RuntimeFieldHandle_SetValueDirect (MonoReflectionField *field, MonoReflectionType *field_type, MonoTypedRef *obj, MonoObject *value, MonoReflectionType *context_type)
{
	MonoClassField *f;

	g_assert (field);
	g_assert (obj);
	g_assert (value);

	f = field->field;
	if (!MONO_TYPE_ISSTRUCT (&f->parent->byval_arg)) {
		mono_set_pending_exception (mono_get_exception_not_implemented (NULL));
		return;
	}

	if (MONO_TYPE_IS_REFERENCE (f->type))
		mono_copy_value (f->type, (guint8*)obj->value + f->offset - sizeof (MonoObject), value, FALSE);
	else
		mono_copy_value (f->type, (guint8*)obj->value + f->offset - sizeof (MonoObject), mono_object_unbox (value), FALSE);
}
