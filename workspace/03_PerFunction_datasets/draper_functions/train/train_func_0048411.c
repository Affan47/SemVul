mono_vcall_trampoline (mgreg_t *regs, guint8 *code, int slot, guint8 *tramp)
{
	MonoObject *this;
	MonoVTable *vt;
	gpointer *vtable_slot;
	MonoMethod *m;
	gboolean need_rgctx_tramp = FALSE;
	gpointer addr;

	trampoline_calls ++;


#ifndef MONO_ARCH_THIS_AS_FIRST_ARG

	g_assert_not_reached ();
#endif


	this = mono_arch_get_this_arg_from_call (regs, code);
	g_assert (this);

	vt = this->vtable;

	if (slot >= 0) {

		vtable_slot = &(vt->vtable [slot]);


		addr = mono_aot_get_method_from_vt_slot (mono_domain_get (), vt, slot);
		if (addr && !vt->klass->valuetype) {
			if (mono_domain_owns_vtable_slot (mono_domain_get (), vtable_slot))
				*vtable_slot = addr;

			return mono_create_ftnptr (mono_domain_get (), addr);
		}


		m = mono_class_get_vtable_entry (vt->klass, slot);

		need_rgctx_tramp = mono_method_needs_static_rgctx_invoke (m, 0);
	} else {

		vtable_slot = &(((gpointer*)vt) [slot]);

		m = NULL;
		need_rgctx_tramp = FALSE;
	}

	return common_call_trampoline (regs, code, m, tramp, vt, vtable_slot, need_rgctx_tramp);
}
