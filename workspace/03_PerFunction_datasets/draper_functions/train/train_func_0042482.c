mono_remoting_invoke (MonoObject *real_proxy, MonoMethodMessage *msg,
		      MonoObject **exc, MonoArray **out_args)
{
	MonoMethod *im = real_proxy->vtable->domain->private_invoke_method;
	gpointer pa [4];


	if (!im) {
		im = mono_class_get_method_from_name (mono_defaults.real_proxy_class, "PrivateInvoke", 4);
		g_assert (im);
		real_proxy->vtable->domain->private_invoke_method = im;
	}

	pa [0] = real_proxy;
	pa [1] = msg;
	pa [2] = exc;
	pa [3] = out_args;

	return mono_runtime_invoke (im, NULL, pa, exc);
}
