mono_signature_get_params (MonoMethodSignature *sig, gpointer *iter)
{
	MonoType** type;
	if (!iter)
		return NULL;
	if (!*iter) {

		if (sig->param_count) {
			*iter = &sig->params [0];
			return sig->params [0];
		} else {

			return NULL;
		}
	}
	type = (MonoType **)*iter;
	type++;
	if (type < &sig->params [sig->param_count]) {
		*iter = type;
		return *type;
	}
	return NULL;
}
