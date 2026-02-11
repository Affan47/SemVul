mono_marshal_get_string_ctor_signature (MonoMethod *method)
{
	MonoMethodSignature *sig = lookup_string_ctor_signature (mono_method_signature (method));
	if (!sig)
		sig = add_string_ctor_signature (method);

	return sig;
}
