mono_metadata_free_type (MonoType *type)
{
	if (type >= builtin_types && type < builtin_types + NBUILTIN_TYPES ())
		return;

	switch (type->type){
	case MONO_TYPE_OBJECT:
	case MONO_TYPE_STRING:
		if (!type->data.klass)
			break;

	case MONO_TYPE_CLASS:
	case MONO_TYPE_VALUETYPE:
		if (type == &type->data.klass->byval_arg || type == &type->data.klass->this_arg)
			return;
		break;
	case MONO_TYPE_PTR:
		mono_metadata_free_type (type->data.type);
		break;
	case MONO_TYPE_FNPTR:
		mono_metadata_free_method_signature (type->data.method);
		break;
	case MONO_TYPE_ARRAY:
		mono_metadata_free_array (type->data.array);
		break;
	}

	g_free (type);
}
