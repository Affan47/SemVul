mono_marshal_need_free (MonoType *t, MonoMethodPInvoke *piinfo, MonoMarshalSpec *spec)
{
	MonoMarshalNative encoding;

	switch (t->type) {
	case MONO_TYPE_VALUETYPE:

		return TRUE;
	case MONO_TYPE_OBJECT:
	case MONO_TYPE_CLASS:
		if (t->data.klass == mono_defaults.stringbuilder_class) {
			gboolean need_free;
			mono_marshal_get_ptr_to_stringbuilder_conv (piinfo, spec, &need_free);
			return need_free;
		}
		return FALSE;
	case MONO_TYPE_STRING:
		encoding = mono_marshal_get_string_encoding (piinfo, spec);
		return (encoding == MONO_NATIVE_LPWSTR) ? FALSE : TRUE;
	default:
		return FALSE;
	}
}
