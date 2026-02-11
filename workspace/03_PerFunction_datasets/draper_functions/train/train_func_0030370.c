mono_gsharedvt_constrained_call (gpointer mp, MonoMethod *cmethod, MonoClass *klass, gboolean deref_arg, gpointer *args)
{
	MonoMethod *m;
	gpointer this_arg;
	gpointer new_args [16];

	m = constrained_gsharedvt_call_setup (mp, cmethod, klass, &this_arg);
	if (!m)
		return NULL;
	if (args && deref_arg) {
		new_args [0] = *(gpointer*)args [0];
		args = new_args;
	}
	if (m->wrapper_type == MONO_WRAPPER_MANAGED_TO_NATIVE) {

		args = new_args;
		args [0] = this_arg;
		this_arg = NULL;
	}
	return mono_runtime_invoke (m, this_arg, args, NULL);
}
