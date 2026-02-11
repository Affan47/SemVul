mono_aot_patch_plt_entry (guint8 *code, guint8 *plt_entry, gpointer *got, mgreg_t *regs, guint8 *addr)
{
	MonoAotModule *amodule;


	if (mono_domain_get () == mono_get_root_domain ()) {
		if (!got) {
			amodule = find_aot_module (code);
			if (amodule)
				got = amodule->got;
		}
		mono_arch_patch_plt_entry (plt_entry, got, regs, addr);
	}
}
