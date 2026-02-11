mini_method_get_rgctx (MonoMethod *m)
{
	if (mini_method_get_context (m)->method_inst)
		return mono_method_lookup_rgctx (mono_class_vtable (mono_domain_get (), m->klass), mini_method_get_context (m)->method_inst);
	else
		return mono_class_vtable (mono_domain_get (), m->klass);
}
