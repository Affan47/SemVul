mono_type_has_exceptions (MonoType *type)
{
	switch (type->type) {
	case MONO_TYPE_CLASS:
	case MONO_TYPE_VALUETYPE:
	case MONO_TYPE_SZARRAY:
		return type->data.klass->exception_type;
	case MONO_TYPE_ARRAY:
		return type->data.array->eklass->exception_type;
	case MONO_TYPE_GENERICINST:
		return mono_generic_class_get_class (type->data.generic_class)->exception_type;
	}
	return FALSE;
}
