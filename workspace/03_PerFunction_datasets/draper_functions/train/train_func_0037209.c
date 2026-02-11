mono_aot_trampoline (mgreg_t *regs, guint8 *code, guint8 *token_info,
					 guint8* tramp)
{
	MonoImage *image;
	guint32 token;
	MonoMethod *method = NULL;
	gpointer addr;
	guint8 *plt_entry;

	trampoline_calls ++;

	image = *(gpointer*)(gpointer)token_info;
	token_info += sizeof (gpointer);
	token = *(guint32*)(gpointer)token_info;

	addr = mono_aot_get_method_from_token (mono_domain_get (), image, token);
	if (!addr) {
		method = mono_get_method (image, token, NULL);
		g_assert (method);


		return mono_magic_trampoline (regs, code, method, tramp);
	}

	addr = mono_create_ftnptr (mono_domain_get (), addr);


	plt_entry = mono_aot_get_plt_entry (code);
	g_assert (plt_entry);

	mono_aot_patch_plt_entry (plt_entry, NULL, regs, addr);

	return addr;
}
