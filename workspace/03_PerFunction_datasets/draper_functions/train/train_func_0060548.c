mono_method_lookup_rgctx (MonoVTable *class_vtable, MonoGenericInst *method_inst)
{
	MonoDomain *domain = class_vtable->domain;
	MonoMethodRuntimeGenericContext *mrgctx;
	MonoMethodRuntimeGenericContext key;

	g_assert (!class_vtable->klass->generic_container);
	g_assert (!method_inst->is_open);

	mono_domain_lock (domain);
	if (!domain->method_rgctx_hash)
		domain->method_rgctx_hash = g_hash_table_new (mrgctx_hash_func, mrgctx_equal_func);

	key.class_vtable = class_vtable;
	key.method_inst = method_inst;

	mrgctx = g_hash_table_lookup (domain->method_rgctx_hash, &key);

	if (!mrgctx) {


		mrgctx = (MonoMethodRuntimeGenericContext*)alloc_rgctx_array (domain, 0, TRUE);
		mrgctx->class_vtable = class_vtable;
		mrgctx->method_inst = method_inst;

		g_hash_table_insert (domain->method_rgctx_hash, mrgctx, mrgctx);


	}

	mono_domain_unlock (domain);

	g_assert (mrgctx);

	return mrgctx;
}
