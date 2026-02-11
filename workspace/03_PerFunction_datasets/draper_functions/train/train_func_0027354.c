add_generic_class (MonoAotCompile *acfg, MonoClass *klass, gboolean force, const char *ref)
{

	if (!acfg->aot_opts.full_aot && !force)
		return;

	add_generic_class_with_depth (acfg, klass, 0, ref);
}
