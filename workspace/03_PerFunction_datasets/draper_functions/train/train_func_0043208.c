mono_object_castclass_unbox (MonoObject *obj, MonoClass *klass)
{
	MonoJitTlsData *jit_tls = NULL;

	if (mini_get_debug_options ()->better_cast_details) {
		jit_tls = mono_native_tls_get_value (mono_jit_tls_id);
		jit_tls->class_cast_from = NULL;
	}

	if (!obj)
		return NULL;

	if (klass->enumtype && obj->vtable->klass == klass->element_class)
		return obj;
	if (mono_object_isinst (obj, klass))
		return obj;

	if (mini_get_debug_options ()->better_cast_details) {
		jit_tls->class_cast_from = obj->vtable->klass;
		jit_tls->class_cast_to = klass;
	}

	mono_raise_exception (mono_exception_from_name (mono_defaults.corlib,
					"System", "InvalidCastException"));

	return NULL;
}
