method_from_method_def_or_ref (MonoImage *m, guint32 tok, MonoGenericContext *context, MonoError *error)
{
	MonoMethod *result = NULL;
	guint32 idx = tok >> MONO_METHODDEFORREF_BITS;

	mono_error_init (error);

	switch (tok & MONO_METHODDEFORREF_MASK) {
	case MONO_METHODDEFORREF_METHODDEF:
		result = mono_get_method_checked (m, MONO_TOKEN_METHOD_DEF | idx, NULL, context, error);
		break;
	case MONO_METHODDEFORREF_METHODREF:
		result = mono_get_method_checked (m, MONO_TOKEN_MEMBER_REF | idx, NULL, context, error);
		break;
	default:
		mono_error_set_bad_image (error, m, "Invalid MethodDefOfRef token %x", tok);
	}

	return result;
}
