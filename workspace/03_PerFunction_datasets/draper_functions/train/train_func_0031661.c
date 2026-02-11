decode_signature_with_target (MonoAotModule *module, MonoMethodSignature *target, guint8 *buf, guint8 **endbuf)
{
	MonoMethodSignature *sig;
	guint32 flags;
	int i, param_count, call_conv;
	guint8 *p = buf;
	gboolean hasthis, explicit_this, has_gen_params;

	flags = *p;
	p ++;
	has_gen_params = (flags & 0x10) != 0;
	hasthis = (flags & 0x20) != 0;
	explicit_this = (flags & 0x40) != 0;
	call_conv = flags & 0x0F;

	if (has_gen_params)
		 decode_value (p, &p);
	param_count = decode_value (p, &p);
	if (target && param_count != target->param_count)
		return NULL;
	sig = (MonoMethodSignature *)g_malloc0 (MONO_SIZEOF_METHOD_SIGNATURE + param_count * sizeof (MonoType *));
	sig->param_count = param_count;
	sig->sentinelpos = -1;
	sig->hasthis = hasthis;
	sig->explicit_this = explicit_this;
	sig->call_convention = call_conv;
	sig->param_count = param_count;
	sig->ret = decode_type (module, p, &p);
	for (i = 0; i < param_count; ++i) {
		if (*p == MONO_TYPE_SENTINEL) {
			g_assert (sig->call_convention == MONO_CALL_VARARG);
			sig->sentinelpos = i;
			p ++;
		}
		sig->params [i] = decode_type (module, p, &p);
	}

	if (sig->call_convention == MONO_CALL_VARARG && sig->sentinelpos == -1)
		sig->sentinelpos = sig->param_count;

	*endbuf = p;

	return sig;
}
