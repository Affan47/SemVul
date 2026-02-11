mono_marshal_get_icall_wrapper (MonoMethodSignature *sig, const char *name, gconstpointer func, gboolean check_exceptions)
{
	MonoMethodSignature *csig, *csig2;
	MonoMethodBuilder *mb;
	MonoMethod *res;
	int i;
	WrapperInfo *info;

	g_assert (sig->pinvoke);

	mb = mono_mb_new (mono_defaults.object_class, name, MONO_WRAPPER_MANAGED_TO_NATIVE);

	mb->method->save_lmf = 1;


	if (sig->hasthis)
		csig2 = signature_dup_add_this (mono_defaults.corlib, sig, mono_defaults.object_class);
	else
		csig2 = signature_dup (mono_defaults.corlib, sig);

#ifndef DISABLE_JIT
	if (sig->hasthis)
		mono_mb_emit_byte (mb, CEE_LDARG_0);

	for (i = 0; i < sig->param_count; i++)
		mono_mb_emit_ldarg (mb, i + sig->hasthis);

	mono_mb_emit_byte (mb, MONO_CUSTOM_PREFIX);
	mono_mb_emit_op (mb, CEE_MONO_JIT_ICALL_ADDR, (gpointer)func);
	mono_mb_emit_calli (mb, csig2);
	if (check_exceptions)
		emit_thread_interrupt_checkpoint (mb);
	mono_mb_emit_byte (mb, CEE_RET);
#endif

	csig = signature_dup (mono_defaults.corlib, sig);
	csig->pinvoke = 0;
	if (csig->call_convention == MONO_CALL_VARARG)
		csig->call_convention = 0;

	res = mono_mb_create_method (mb, csig, csig->param_count + 16);
	mono_mb_free (mb);

	info = mono_wrapper_info_create (res, WRAPPER_SUBTYPE_ICALL_WRAPPER);
	info->d.icall.func = (gpointer)func;
	mono_marshal_set_wrapper_info (res, info);

	return res;
}
